# Encoding

The purpose of this section of the project is to convert a given file into a morse-code like sequence, which can then be passed to the **Translation Layer**.

## Morse Code
Morse Code is traversable via a binary tree. This allows for more common characters to be transmitted over a shorter period of time, for example T and E are single-tone characters.

## Our System
Our system will be similar, but will instead be adapted for the transfer of raw bytes of data. Data will always be transferred in 8 bit sections, so our binary tree will be mapping them together in a way that makes sense while still optimising for time.

Some of the most common bytes in data are null bytes, (all zeros) and maxed-out bytes (all ones), so these will be our starting split.

### Exact Encoding
`.` will refer to a null byte. `-` referrs to a max-byte.

After these, they will be encoded as a simple binary tree, in which a `-` refers to a flip in the the (N+1)th bit, with N being the current "depth". Some examples:

 - `..-` : `00100000`
 - `-..-...-` : `11101110`

So our tree will have a max depth of 8.
