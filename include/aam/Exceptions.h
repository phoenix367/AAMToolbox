/* Active Appearance Model toolbox
 * Copyright (C) 2012 Ivan Gubochkin
 * e-mail: jhng@yandex.ru
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   Exceptions.h
 * Author: Иван Губочкин
 *
 * Created on 9 Август 2012 г., 0:15
 */

#ifndef AAM_EXCEPTIONS_H
#define	AAM_EXCEPTIONS_H

#include <exception>
#include <string>

namespace aam
{
    class AAMException : public std::exception
    {
    public:
        AAMException(const std::string& msg) throw()
        : exceptionMessage(msg)
        {
        }

        virtual ~AAMException() throw()
        {
        }

        virtual const char* what() const throw()
        {
            return this->exceptionMessage.c_str();
        }

    protected:
        std::string exceptionMessage;
    };

    class InvalidImageFormat : public AAMException
    {
    public:
        InvalidImageFormat() throw()
        : AAMException("Invalid image format")
        {
        }

        virtual ~InvalidImageFormat() throw()
        {
        }
    };

    class InvalidMarkupFile : public AAMException
    {
    public:
        InvalidMarkupFile() throw()
        : AAMException("Invalid markup file format")
        {
        }

        virtual ~InvalidMarkupFile() throw()
        {
        }
    };

    class FileNotFoundError : public AAMException
    {
    public:
        FileNotFoundError() throw()
        : AAMException("File not found")
        {
        }

        virtual ~FileNotFoundError() throw()
        {
        }
    };

    class InternalException : public AAMException
    {
    public:
        InternalException() throw()
        : AAMException("An internal exception of AAMToolbox")
        {
        }

        virtual ~InternalException() throw()
        {
        }
    };

    class InvalidArgumentException : public AAMException
    {
    public:
        InvalidArgumentException() throw()
        : AAMException("Invalid argument")
        {
        }

        virtual ~InvalidArgumentException() throw()
        {
        }
    };

    class InvalidModelFileException : public AAMException
    {
    public:
        InvalidModelFileException() throw()
        : AAMException("Invalid AAM model file")
        {
        }

        virtual ~InvalidModelFileException() throw()
        {
        }
    };

    class NotInitializedException : public AAMException
    {
    public:
        NotInitializedException() throw()
        : AAMException("Object not initialized")
        {
        }

        virtual ~NotInitializedException() throw()
        {
        }
    };
}

#endif	/* AAM_EXCEPTIONS_H */
