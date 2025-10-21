#pragma once
#include "sdk/amxxmodule.h"

namespace amxx_bcrypt
{
    static cell AMX_NATIVE_CALL bcrypt_hash(AMX* amx, cell* params);
    static cell AMX_NATIVE_CALL bcrypt_check(AMX* amx, cell* params);

    AMX_NATIVE_INFO BcryptNatives[] =
    {
        { "bcrypt_hash", bcrypt_hash },
        { "bcrypt_check", bcrypt_check },
        { NULL, NULL }
    };
};

