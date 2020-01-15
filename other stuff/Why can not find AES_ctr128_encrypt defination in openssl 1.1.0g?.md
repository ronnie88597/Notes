# Why can not find AES_ctr128_encrypt defination in openssl 1.1.0g?

AES_ctr128_encrypt is removed from openssl 1.1.0g

You can use `CRYPTO_ctr128_encrypt` instead of  `AES_ctr128_encrypt`



```c++
AES_ctr128_encrypt(
  in, 
  out, 
  len, 
  &cipher->aes_key->key, 
  cipher->aes_key->IV, 
  buffer, 
  &num); // removed from openssl 1.1.0g


CRYPTO_ctr128_encrypt(
  in, 
  out, 
  len, 
  &cipher->aes_key->key, 
  cipher->aes_key->IV, 
  buffer, 
  &num, 
  (block128_f)AES_encrypt); // instead
```