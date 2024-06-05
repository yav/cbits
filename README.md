This library (work in progress) defines functions for working with
arbitrary sized bit-vectors.  The library has two sets of algorithms:

  * the "small" representation for sizes [1 .. 64] uses `uint64_t`
  * the "large" representation for sizes [65 .. ) uses an array of `uint32_t`

All functions in the library have an explicit parameter specifying
the widths of the bit-vectors involved.

In addition, we plan to provide a 3rd representation, which is a `union` of
"small" and "large", and the width argument will be used to choose
between the alternatives of the union.   Thus, the width is used as
the "tag" of the corresponding algebraic datatype, but it is not stored
directly with the value.

Bit-vectors that do not fit in a representation type exactly, are placed
in the *most significant* bits of the representation, with the least
significant unused bits set to 0.   Essentially, if `x` is an `N`-bit vector
(`1 <= N <= 64`), it will be represented as `x * 2^(64-N)` (aka `x << (64-N)`).
The same holds for large bit-vectors, where the least significant element
of the representation array may contain up to 31 bits of padding.
This is useful, because it allows many operations to be performed
directly on the normalized representation, without having to change
representations.

For the large representation, the least significant bits of the value
are in the first array element, and the most significant bits are in the
last array element.


