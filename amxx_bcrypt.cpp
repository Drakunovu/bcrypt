#include <stdio.h>
#include <string>
#include <string.h>
#include <stdexcept>

#include "amxx_bcrypt.h"
#include "bcrypt_lib/bcrypt.h"

#ifndef BCRYPT_HASHSIZE
#define BCRYPT_HASHSIZE 61
#endif

void OnAmxxAttach()
{
    MF_AddNatives(amxx_bcrypt::BcryptNatives);
}

void OnAmxxDetach()
{
}

cell AMX_NATIVE_CALL amxx_bcrypt::bcrypt_hash(AMX* amx, cell* params)
{
    if (params[0] != 4 * sizeof(cell))
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_hash: incorrect number of arguments (%d, expected 4)", params[0] / sizeof(cell));
        return 0;
    }

    int passwordLen = 0;
    int maxOutputLenChars = params[4];

    char* password_cstr = MF_GetAmxString(amx, params[1], 0, &passwordLen);
    int cost_factor = params[2];

    if (!password_cstr || passwordLen == 0) {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_hash: Invalid or empty password provided.");
        return 0;
    }
    if (cost_factor < 4 || cost_factor > 31)
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_hash: cost_factor must be between 4 and 31 (was %d)", cost_factor);
        return 0;
    }
    if (maxOutputLenChars < (BCRYPT_HASHSIZE - 1))
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_hash: hash buffer too small (need capacity for %d chars, got %d)", BCRYPT_HASHSIZE - 1, maxOutputLenChars);
        return 0;
    }

    try
    {
        std::string password_str(password_cstr);
        std::string hash_output_str = bcrypt::generateHash(password_str, cost_factor);

        if (hash_output_str.length() >= (size_t)maxOutputLenChars + 1)
        {
            MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_hash: generated hash (%d chars) is too long for the provided buffer capacity (%d chars).", (int)hash_output_str.length(), maxOutputLenChars);
            return 0;
        }

        MF_SetAmxString(amx, params[3], hash_output_str.c_str(), maxOutputLenChars + 1);

        return 1;
    }
    catch (const std::exception& e)
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_hash: Exception during hashing: %s", e.what());
        return 0;
    }
    catch (...)
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_hash: Unknown exception during hashing.");
        return 0;
    }
}

cell AMX_NATIVE_CALL amxx_bcrypt::bcrypt_check(AMX* amx, cell* params)
{
    if (params[0] != 2 * sizeof(cell))
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_check: incorrect number of arguments (%d, expected 2)", params[0] / sizeof(cell));
        return 0;
    }

    int passwordLen = 0;
    int hashLen = 0;

    char* password_cstr = MF_GetAmxString(amx, params[1], 0, &passwordLen);
    char* hash_cstr = MF_GetAmxString(amx, params[2], 1, &hashLen);

    if (!password_cstr) {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_check: Invalid password string.");
        return 0;
    }
    if (!hash_cstr || hashLen == 0) {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_check: Invalid or empty hash string provided.");
        return 0;
    }

    try
    {
        std::string password_str(password_cstr);
        std::string hash_str(hash_cstr);

        bool match = bcrypt::validatePassword(password_str, hash_str);

        return match ? 1 : 0;
    }
    catch (const std::exception& e)
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_check: Exception during validation: %s", e.what());
        return 0;
    }
    catch (...)
    {
        MF_LogError(amx, AMX_ERR_NATIVE, "bcrypt_check: Unknown exception during validation.");
        return 0;
    }
}

