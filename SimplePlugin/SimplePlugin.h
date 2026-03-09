/*
* If not stated otherwise in this file or this component's LICENSE file the
* following copyright and licenses apply:
*
* Copyright 2025 [PLEASE ADD COPYRIGHT NAME!]
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#pragma once

#include "Module.h"
#include <interfaces/ISimplePlugin.h>

namespace Thunder {
namespace Plugin {

    class SimplePlugin : public PluginHost::IPlugin, public PluginHost::JSONRPC, public Exchange::ISimplePlugin {
    public:
        SimplePlugin(const SimplePlugin&) = delete;
        SimplePlugin& operator=(const SimplePlugin&) = delete;
        SimplePlugin(SimplePlugin&&) = delete;
        SimplePlugin& operator=(SimplePlugin&&) = delete;

        SimplePlugin()
            : PluginHost::IPlugin()
            , PluginHost::JSONRPC()
            , Exchange::ISimplePlugin()
            , _adminLock()
            , _simplepluginNotification()
        {
        }

        ~SimplePlugin() override = default;
    private:
    public:
        // IPlugin Methods
        const string Initialize(PluginHost::IShell* service) override;
        void Deinitialize(PluginHost::IShell* service) override;
        string Information() const override;

        // ISimplePlugin methods

        Core::hresult Register(ISimplePlugin::INotification* /* sink */) override;

        Core::hresult Unregister(const ISimplePlugin::INotification* /* sink */) override;

        Core::hresult Status() override;

        BEGIN_INTERFACE_MAP(SimplePlugin)
            INTERFACE_ENTRY(PluginHost::IPlugin)
            INTERFACE_ENTRY(PluginHost::IDispatcher)
            INTERFACE_ENTRY(Exchange::ISimplePlugin)
        END_INTERFACE_MAP

    private:
        using SimplePluginNotificationContainer = std::vector<Exchange::ISimplePlugin::INotification*>;

        mutable Core::CriticalSection _adminLock;
        SimplePluginNotificationContainer _simplepluginNotification;
    };
} // Plugin
} // Thunder