#pragma once

#include "Entity.h"

class ComponentPoolBase {
public:
  virtual ~ComponentPoolBase() noexcept             = default;
  virtual void   Remove(Entity e) noexcept          = 0;
  virtual size_t GetSize() const noexcept           = 0;
  virtual bool   HasEntity(Entity e) const noexcept = 0;
};
