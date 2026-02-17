#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "ComponentPool.h"
#include "ComponentPoolBase.h"

class World {
public:
  World() noexcept;

  inline Entity CreateEntity() noexcept { return m_next_entity++; }

  template <typename T>
  ComponentPool<T>* GetOrRegisterPool() noexcept {
    std::type_index key = std::type_index(typeid(T));
    auto            it  = m_pools.find(key);
    if (it == m_pools.end()) {
      auto [inserted, _] = m_pools.emplace(key, std::make_unique<ComponentPool<T>>());
      return static_cast<ComponentPool<T>*>(inserted->second.get());
    }
    return static_cast<ComponentPool<T>*>(it->second.get());
  }

  template <typename T>
  void AddComponent(Entity e, T c) noexcept {
    GetOrRegisterPool<T>()->Insert(e, c);
  }

  template <typename First, typename... Rest, typename F>
  void Each(F fn) {
    auto* pool = GetOrRegisterPool<First>();
    for (auto it = pool->EntityBegin(); it != pool->EntityEnd(); ++it) {
      auto [entity, first] = *it;
      if ((GetOrRegisterPool<Rest>()->HasEntity(entity) && ...)) {
        fn(entity, first, GetOrRegisterPool<Rest>()->Get(entity)...);
      }
    }
  }

private:
  template <typename... Ts>
  ComponentPoolBase* SmallestPool() {
    ComponentPoolBase* result   = nullptr;
    size_t             min_size = SIZE_MAX;
    for (auto* pool : {static_cast<ComponentPoolBase*>(GetOrRegisterPool<Ts>())...}) {
      if (pool->size() < min_size) {
        min_size = pool->size();
        result   = pool;
      }
    }
    return result;
  }

  Entity                                                                  m_next_entity;
  std::unordered_map<std::type_index, std::unique_ptr<ComponentPoolBase>> m_pools;
};
