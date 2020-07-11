# DBPBE
DBPBE (Distance Between Points Based Encryption)

This project is a proof of concept as of now

See the documentation [here](https://dbpbe.com)

## Compiling

there are a bunch of testing things that i have built into the main cpp file:

- mode 01 = testing for datatype casting
- mode 02 = testing for datatype casting 2.0
- mode 03 = testing for conversions
- mode 04 = testing for conversions 2.0
- mode 05 = testing string inputs
- mode 06 = testing string inputs into list
- mode 07 = testing key generation based on passphrase
- mode 08 = testing key generation based on rand
- mode 09 = testing converting char to distances
- mode 10 = testing converting string to distances
- mode 11 = testing converting to and from distances with chars
- mode 12 = testing converting to and from distances with strings

to compile:

```shell
$ make testnum=<MODENUMBER>
```
