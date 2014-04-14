/**
 * Copyright 2013-2014 Rene Widera, Felix Schmitt
 *
 * This file is part of libPMacc. 
 * 
 * libPMacc is free software: you can redistribute it and/or modify 
 * it under the terms of of either the GNU General Public License or 
 * the GNU Lesser General Public License as published by 
 * the Free Software Foundation, either version 3 of the License, or 
 * (at your option) any later version. 
 * libPMacc is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * GNU General Public License and the GNU Lesser General Public License 
 * for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * and the GNU Lesser General Public License along with libPMacc. 
 * If not, see <http://www.gnu.org/licenses/>. 
 */ 
 

#pragma once

#include <stdexcept>
#include <string>

#include <boost/program_options/options_description.hpp>

#include "pluginSystem/INotify.hpp"

namespace PMacc
{
    namespace po = boost::program_options;

    /*
     * Exception for plugin or plugin-management related errors.
     */
    class PluginException : public std::runtime_error
    {
    public:

        PluginException(const char* message) : std::runtime_error(message)
        {
        }

        PluginException(std::string message) : std::runtime_error(message.c_str())
        {
        }
    };

    /*
     * IPlugin interface.
     */
    class IPlugin : public INotify
    {
    public:

        IPlugin() :
        loaded(false)
        {

        }

        virtual ~IPlugin()
        {
        }

        virtual void load()
        {
            pluginLoad();
            loaded = true;
        }

        virtual void unload()
        {
            pluginUnload();
            loaded = false;
        }

        bool isLoaded()
        {
            return loaded;
        }

        /**
         * Notifies plugins that a (restartable) checkpoint should be created for this timestep.
         * 
         * @param currentStep cuurent simulation iteration step
         */
        virtual void checkpoint(uint32_t currentStep) = 0;
        
        /**
         * Restart notification callback.
         * 
         * 
         * @param restartStep simulation iteration step to restart from
         */
        virtual void restart(uint32_t restartStep) = 0;

        /**
         * Register command line parameters for this plugin.
         * Parameters are parsed and set prior to plugin load.
         * 
         * @param desc boost::program_options description
         */
        virtual void pluginRegisterHelp(po::options_description& desc) = 0;

        /**
         * Return the name of this plugin for status messages.
         * 
         * @return plugin name
         */
        virtual std::string pluginGetName() const = 0;

    protected:
        virtual void pluginLoad()
        {
            /* override this function if necessary */
        }

        virtual void pluginUnload()
        {
            /* override this function if necessary */
        }

        bool loaded;
    };
}