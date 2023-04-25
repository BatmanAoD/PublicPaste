A type system without "full generics", and specifically only
monomorphizing container definitions (similar to how `map` and
`[]` work "magically" in Go), but permitting:
* user-defined containers (map, vector, other)
* ...with (limited) covariance
* Possibly no contravariance?

A container definition is *automatically* given RTTI for the *element* types
(including keys, put possibly also recursively, e.g. `map[A]map[B]C` could have
separate RTTI for A, B, and C?)

Containers must define iteration and lookups, but there must be a
compiler-feature to wrap the _key_ and _item_ types with an RTTI wrapper

Pattern matching is needed to go from a container with RTTI to a concrete
container type.

Covariance for function signatures, but *not* for expressions: i.e. these
dynamically-typed containers would not follow the Liskov principle.

---

some useful containers for users to define:
* maps (with various means of lookups, e.g. BTree, alternate hash algos)
* vector
* LRU
* ordered map
* set
* ring buffer

Don't want users to define:
* allocation
* memory address locations

Possibly want to permit control over:
* reallocation trigger
* reallocation growth rate

What are the value semantics for the containers? Can users control that?

---

```
type PMap container<A:Hash,B> {
  // implicit: RTTI for A,B
  // `std` is some standard-lib type for dynamically-growing memory;
  // it uses the same interface as user-defined containers ([], []=, iter)
  // ...it is a sparsely-populated ring-buffer, i.e. effectively
  // Vec<Option<(A,*B)>> with iteration starting at an arbitrary index
  data: ringbuf<(A,*B)>,
  // implicit: `size()` -- ...how does this work? Must be separate
  // counter...right? Or defer to `data`?
}
```

In expressions, `PMap` means "dynamically-typed `PMap`", i.e. with an RTTI
pointer. `PMap<foo,bar>` means a concrete `PMap` type.

Assignment only works with `PMap<foo,bar>`. `PMap`->`PMap<foo,bar>` can be done
with pattern matching.

These are the "magic" functions for containers (using `Ctr<A,*B>` as a user-defined name):

```
  Ctr[A] -> Option<*B>
  // `gen` is a keyword for a generator
  // Note: `iter` (especially for std types) should never return
  // "empty"/"missing" items (e.g. for a sparsely-populated vector, the empty
  // items are skipped)
  Ctr.iter() -> gen<A, *B>
  Ctr[A]=*B
  // ...optionally:
  Ctr.resize(usize)
  Ctr.index_iter() -> gen<A>
  Ctr.iter_from(A) -> gen<(A, *B)>
  Ctr.has(A) -> bool
  Ctr[A..A] -> gen<*B>
  // For sparse containers to find "next empty" from an index, and populate it
  Ctr.set_next(A, *B) 
  // For non-assiociative containers (type `<usize,*B>`):
  Ctr.append(*B)
  Ctr.extend(gen<*B>) // ... `gen` should have size-hint when possible
```
...other than syntax, what's "magic" about these? In particular, are the ones
with normal function-call syntax "magic" at all?

User-defined functions:

```
func (p *PMap<A,B>)[index A] -> Option<*B> {
  let start = index.hash() % p.data.size();
  // ...I don't actually know what the algorithm should be, e.g. how it works
  // in Python. Is there a limit to how many entries to check?
  // ...what should the syntax be for "looping around" the ring buffer?
  for (a, b) := p.data.iter_from(start) {
    if a == index {
      return Some(b)  // is explicit 'Some' necessary?
    }
  }
  return None // is there a more convenient way than explicit Some/None?
}

func (p *PMap<A,B>)[index A]=(value *B) {
  let start = index.hash() % p.data.size();
  p.data.set_next(start, value)
}

// `gen`: keyword for "generator"
// Note: this basically just "defers" to `p.data`. Could use a special syntax for that
func (p *PMap<A,B>)iter() -> gen<A, *B> {
  for (a, b) := p.data.iter() {
    yield (a, b)
  }
}
```

Using `PMap`:

```
func DoStuff(p PMap) {
  for (a, b) := p.iter() {
    // ...a & b are of type `any` here; they are "wrapped" in interface types
  }
}

func DoSomethingSpecific(p PMap) {
  match p {
  case PMap<string, PMap<string, any>>:
    new_map := PMap<string, any>{}
    new_map["inner"] = 37.0
    p["foo"] = new_map
  default:
    ...
  }
}
```
