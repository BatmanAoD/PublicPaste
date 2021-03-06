Rust is fundamentally different from every other mainstream language I know of, because its design has some core tenets that are actually opposed to those of languages like JavaScript:

* Humans are prone to error; software tools should do everything in their power to help catch those errors early.
* Complicated design issues should be exposed and made legible, not obscured in pursuit of “easiness”.
* Tradeoffs should be “overcome” when possible: a novel solution to a known problem may provide an entirely different cost/benefit analysis than the existing solutions.

The most well-known feature demonstrating all three principles is the “borrow checker”, which forces lifetimes and ownership to be explicit in the code. This makes it more difficult to get things to compile than in C++, but provides better safety guarantees than even garbage collected languages have (especially in multithreaded systems), without any runtime cost.

I don't trust developers, including myself. There are a few languages that similarly seem to “distrust” developers, but in different ways. Java and Go are the most prominent, I think; they seem to be designed with minimal feature sets and mechanisms that reduce developer control over runtime behavior. Rust is the only general-purpose language I know of that attempts to reduce error not by eliminating features and moving complexity into the runtime (i.e. with GC and a built-in parallelism model), but by forcing developers to either provide the compiler with a statically verifiable solution to ownership and threading issues, or to explicitly opt out of static verification for limited blocks of code (e.g. for accessing raw memory).

(There are proof-languages like Coq and Idris that require such statically verifiable code, but these don't seem to be general-purpose because the burden of such proofs is so high.)
