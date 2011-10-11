/*
 * libcryptoplus - C++ portable OpenSSL cryptographic wrapper library.
 * Copyright (C) 2010-2011 Julien Kauffmann <julien.kauffmann@freelan.org>
 *
 * This file is part of libcryptoplus.
 *
 * libcryptoplus is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libcryptoplus is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 *
 * If you intend to use libcryptoplus in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file verify_param.hpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief A class that holds X509 verification parameters.
 */

#ifndef CRYPTOPLUS_X509_VERIFY_PARAM_HPP
#define CRYPTOPLUS_X509_VERIFY_PARAM_HPP

#include "../pointer_wrapper.hpp"
#include "../error/cryptographic_exception.hpp"

#include <openssl/x509.h>
#include <openssl/x509v3.h>

namespace cryptoplus
{
	namespace x509
	{
		/**
		 * \brief A class that holds X509 verification parameters.
		 *
		 * A verify_param instance has the same semantic as a X509_VERIFY_PARAM* pointer, thus two copies of the same instance share the same underlying pointer.
		 *
		 * \warning Always check for the object not to be NULL before calling any of its method. Calling any method (except raw()) on a null object has undefined behavior.
		 */
		class verify_param: public pointer_wrapper<X509_VERIFY_PARAM>
		{
			public:

				/**
				 * \brief Create a new verify_param.
				 * \return The verify_param.
				 *
				 * If allocation fails, a cryptographic_exception is thrown.
				 */
				static verify_param create();

				/**
				 * \brief Take ownership of a specified X509_VERIFY_PARAM pointer.
				 * \param ptr The pointer. Cannot be NULL.
				 * \return A verify_param.
				 */
				static verify_param take_ownership(pointer ptr);

				/**
				 * \brief Create a new empty X509 verify_param.
				 */
				verify_param();

				/**
				 * \brief Create a X509 verify_param by *NOT* taking ownership of an existing X509_VERIFY_PARAM* pointer.
				 * \param ptr The X509_VERIFY_PARAM* pointer.
				 * \warning The caller is still responsible for freeing the memory.
				 */
				verify_param(pointer ptr);

			private:

				verify_param(pointer _ptr, deleter_type _del);
		};

		/**
		 * \brief Compare two verify_param instances.
		 * \param lhs The left argument.
		 * \param rhs The right argument.
		 * \return true if the two verify_param instances share the same underlying pointer.
		 */
		bool operator==(const verify_param& lhs, const verify_param& rhs);

		/**
		 * \brief Compare two verify_param instances.
		 * \param lhs The left argument.
		 * \param rhs The right argument.
		 * \return true if the two verify_param instances do not share the same underlying pointer.
		 */
		bool operator!=(const verify_param& lhs, const verify_param& rhs);

		inline verify_param verify_param::create()
		{
			pointer _ptr = X509_VERIFY_PARAM_new();

			error::throw_error_if_not(_ptr);

			return take_ownership(_ptr);
		}
		inline verify_param verify_param::take_ownership(pointer _ptr)
		{
			error::throw_error_if_not(_ptr);

			return verify_param(_ptr, deleter);
		}
		inline verify_param::verify_param()
		{
		}
		inline verify_param::verify_param(pointer _ptr) : pointer_wrapper<value_type>(_ptr, null_deleter)
		{
		}
		inline verify_param::verify_param(pointer _ptr, deleter_type _del) : pointer_wrapper<value_type>(_ptr, _del)
		{
		}
		inline bool operator==(const verify_param& lhs, const verify_param& rhs)
		{
			return lhs.raw() == rhs.raw();
		}
		inline bool operator!=(const verify_param& lhs, const verify_param& rhs)
		{
			return lhs.raw() != rhs.raw();
		}
	}
}

#endif /* CRYPTOPLUS_X509_VERIFY_PARAM_HPP */
