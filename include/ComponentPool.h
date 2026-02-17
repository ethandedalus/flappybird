#pragma once

#include <cassert>
#include <unordered_map>
#include <vector>

#include "ComponentPoolBase.h"
#include "Entity.h"

template <typename T>
class ComponentPool : public ComponentPoolBase {
public:
  ComponentPool() noexcept {
  }

  void Insert(Entity e, T component) {
    assert(!HasEntity(e));
    m_entity_to_index[e] = m_components.size();
    m_index_to_entity.push_back(e);
    m_components.push_back(std::move(component));
  }

  void Remove(Entity e) noexcept override {
    assert(HasEntity(e));
    size_t index = m_entity_to_index[e];
    size_t last  = m_components.size() - 1;

    if (index != last) {
      Entity last_entity             = m_index_to_entity[last];
      m_components[index]            = std::move(m_components[last]);
      m_index_to_entity[index]       = last_entity;
      m_entity_to_index[last_entity] = index;
    }

    m_components.pop_back();
    m_index_to_entity.pop_back();
    m_entity_to_index.erase(e);
  }

  bool HasEntity(Entity e) const noexcept override {
    return m_entity_to_index.contains(e);
  }

  T& Get(Entity e) {
    return m_components[m_entity_to_index.at(e)];
  }

  size_t GetSize() const noexcept override { return m_components.size(); }

  std::vector<T>::iterator begin() { return m_components.begin(); }
  std::vector<T>::iterator end() { return m_components.end(); }

  struct Iterator {
    size_t         index;
    ComponentPool& pool;
    auto           operator*() { return std::pair<Entity, T&>{pool.m_index_to_entity[index], pool.m_components[index]}; }
    Iterator&      operator++() {
      ++index;
      return *this;
    }
    bool operator!=(const Iterator& o) const { return index != o.index; }
  };

  Iterator EntityBegin() { return {0, *this}; }
  Iterator EntityEnd() { return {m_components.size(), *this}; }

private:
  std::vector<T>                     m_components;
  std::vector<Entity>                m_index_to_entity;
  std::unordered_map<Entity, size_t> m_entity_to_index;
};
