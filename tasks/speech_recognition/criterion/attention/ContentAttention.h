/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "AttentionBase.h"

namespace fl {
namespace task {
namespace asr {

class ContentAttention : public AttentionBase {
 public:
  ContentAttention(bool keyValue = false) : keyValue_(keyValue) {}

  std::pair<fl::Variable, fl::Variable> forward(
      const fl::Variable& state,
      const fl::Variable& xEncoded,
      const fl::Variable& prevAttn,
      const fl::Variable& attnWeight) override;

  std::string prettyString() const override;

 private:
  bool keyValue_;

  FL_SAVE_LOAD_WITH_BASE(AttentionBase, fl::versioned(keyValue_, 1))
};

class NeuralContentAttention : public AttentionBase {
 public:
  NeuralContentAttention() {}
  explicit NeuralContentAttention(int dim, int layers = 1);

  std::pair<fl::Variable, fl::Variable> forward(
      const fl::Variable& state,
      const fl::Variable& xEncoded,
      const fl::Variable& prevAttn,
      const fl::Variable& attnWeight) override;

  std::string prettyString() const override;

 private:
  FL_SAVE_LOAD_WITH_BASE(AttentionBase)
};
}
}
}

CEREAL_REGISTER_TYPE(fl::task::asr::ContentAttention)
CEREAL_CLASS_VERSION(fl::task::asr::ContentAttention, 1)
CEREAL_REGISTER_TYPE(fl::task::asr::NeuralContentAttention)
