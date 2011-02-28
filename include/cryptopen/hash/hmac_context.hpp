/*
 * libcryptopen - C++ portable OpenSSL cryptographic wrapper library.
 * Copyright (C) 2010-2011 Julien Kauffmann <julien.kauffmann@freelan.org>
 *
 * This file is part of libcryptopen.
 *
 * libcryptopen is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * libcryptopen is distributed in the hope that it will be useful, but
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
 * If you intend to use libcryptopen in a commercial software, please
 * contact me : we may arrange this for a small fee or no fee at all,
 * depending on the nature of your project.
 */

/**
 * \file hmac_context.hpp
 * \author Julien KAUFFMANN <julien.kauffmann@freelan.org>
 * \brief A HMAC context class.
 */

#ifndef CRYPTOPEN_HASH_HMAC_CONTEXT_HPP
#define CRYPTOPEN_HASH_HMAC_CONTEXT_HPP

#include <openssl/hmac.h>

namespace cryptopen
{
	namespace hash
	{
		/**
		 * \brief A HMAC context class.
		 *
		 * The hmac_context class ease the computation of a HMAC.
		 *
		 * The list of the available hash methods depends on the version of OpenSSL and can be found on the man page of EVP_DigestInit().
		 */
		class hmac_context
		{
			public:

				/**
				 * \brief Create a new hmac_context.
				 */
				hmac_context();

				/**
				 * \brief Create a new hmac_context by taking ownership of a specified HMAC_CTX.
				 * \param ctx The HMAC_CTX. ctx must have been initialized with HMAC_CTX_init().
				 *
				 * The caller is no longer responsible for calling HMAC_CTX_cleanup() on the specified context.
				 */
				hmac_context(const HMAC_CTX& ctx) : m_ctx(ctx) {}

				/**
				 * \brief Destroy a hmac_context.
				 *
				 * Calls HMAC_CTX_cleanup() on the internal HMAC_CTX.
				 */
				~hmac_context();

				/**
				 * \brief Initialize the hmac_context.
				 * \param key The key to use. If key is NULL, the previously used key is taken.
				 * \param key_len The key length. If key is NULL, key_len is not used.
				 * \param md The message digest (hash) algorithm to use. If md is NULL, the previously used message digest algorithm is taken.
				 * \param impl The engine to use. Default is NULL which indicates that no engine should be used.
				 * \return true on success.
				 *
				 * The list of the available hash methods depends on the version of OpenSSL and can be found on the man page of EVP_DigestInit().
				 */
				bool initialize(const void* key, size_t key_len, const EVP_MD* md, ENGINE* impl = NULL);

				/**
				 * \brief Update the hmac_context with some data.
				 * \param data The data buffer.
				 * \param len The data length.
				 * \return true on success.
				 */
				bool update(const void* data, size_t len);

				/**
				 * \brief Finalize the hmac_context and get the resulting buffer.
				 * \param md The resulting buffer. Cannot be NULL.
				 * \param len The length of md. Will be updated to indicate the used size after the call.
				 * \return true on success.
				 */
				bool finalize(void* md, size_t& len);

			private:

				HMAC_CTX m_ctx;
		};

		inline hmac_context::hmac_context()
		{
			HMAC_CTX_init(&m_ctx);
		}

		inline hmac_context::~hmac_context()
		{
			HMAC_CTX_cleanup(&m_ctx);
		}

		inline bool hmac_context::initialize(const void* key, size_t key_len, const EVP_MD* md, ENGINE* impl)
		{
			return HMAC_Init_ex(&m_ctx, key, static_cast<int>(key_len), md, impl);
		}
		
		inline bool hmac_context::update(const void* data, size_t len)
		{
			return HMAC_Update(&m_ctx, static_cast<const unsigned char*>(data), static_cast<int>(len));
		}
	}
}

#endif /* CRYPTOPEN_HASH_HMAC_CONTEXT_HPP */
