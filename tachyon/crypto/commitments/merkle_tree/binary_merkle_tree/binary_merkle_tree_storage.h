// Use of this source code is governed by a Apache-2.0 style license that
// can be found in the LICENSE.lambdaworks.

#ifndef TACHYON_CRYPTO_COMMITMENTS_MERKLE_TREE_BINARY_MERKLE_TREE_BINARY_MERKLE_TREE_STORAGE_H_
#define TACHYON_CRYPTO_COMMITMENTS_MERKLE_TREE_BINARY_MERKLE_TREE_BINARY_MERKLE_TREE_STORAGE_H_

#include <stddef.h>

namespace tachyon::crypto {

template <typename HashTy>
class BinaryMerkleTreeStorage {
 public:
  virtual ~BinaryMerkleTreeStorage() = default;

  virtual void Allocate(size_t size) = 0;
  virtual size_t GetSize() const = 0;
  virtual const HashTy& GetHash(size_t i) const = 0;
  virtual void SetHash(size_t i, const HashTy& hash) = 0;
};

}  // namespace tachyon::crypto

#endif  // TACHYON_CRYPTO_COMMITMENTS_MERKLE_TREE_BINARY_MERKLE_TREE_BINARY_MERKLE_TREE_STORAGE_H_
