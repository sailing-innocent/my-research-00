# Notes When Building Sail

Strucutures Having Eigen Members

If you define a structure having members of fixed-size vectorizable Eigen types, you must ensure the calling operator `new` on it allocated propery aligned buffers.

