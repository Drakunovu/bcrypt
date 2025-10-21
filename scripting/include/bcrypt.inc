#if defined _amxx_bcrypt_included
  #endinput
#endif
#define _amxx_bcrypt_included

/**
 * Hashes a password using bcrypt.
 *
 * @param password      The password string to hash.
 * @param cost_factor   The cost factor (work factor) for hashing (typically 4-12, higher is slower but more secure).
 * @param hash_output   Buffer to store the resulting hash string.
 * @param output_len    Maximum length of the hash_output buffer (should be at least 61).
 *
 * @return              1 on success, 0 on failure.
 * @error               Logs an error message if hashing fails or parameters are invalid.
 */
native bcrypt_hash(const password[], cost_factor, hash_output[], output_len);

/**
 * Checks if a given password matches a bcrypt hash.
 *
 * @param password      The plain text password to check.
 * @param hash          The bcrypt hash string to compare against.
 *
 * @return              true if the password matches the hash, false otherwise.
 * @error               Logs an error message if parameters are invalid or comparison fails unexpectedly.
 */
native bool:bcrypt_check(const password[], const hash[]);
