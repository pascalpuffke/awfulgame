#pragma once

#include <fmt/color.h>
#include <fmt/format.h>
#include <memory>
#include <string>
#include <robin_hood.h>
#include <optional>

namespace Registries {

template <typename T>
class Registry {
public:
    explicit Registry(std::string &&name)
            : m_name(std::move(name))
    {
    }

    virtual ~Registry() = default;

    virtual void load(const std::string &key, const T &resource)
    {
        if (m_registry.contains(key)) {
            fmt::print(fg(fmt::color::yellow), "[{}] WARN: Resource {} already exists\n", m_name, key);
            return;
        }

        m_registry[key] = std::make_shared<T>(resource);
        fmt::print(fg(fmt::color::light_green), "[{}] Registered resource {}\n", m_name, key);
    }

    virtual void loadAll(robin_hood::unordered_map<std::string, T> &&resources)
    {
        for (const auto &[key, resource]: resources) {
            load(key, resource);
        }
    }

    [[nodiscard]] virtual std::optional<std::shared_ptr<T>> get(const std::string &key) const
    {
        // Instead of manually checking if the key exists using std::map::contains(),
        // catching a possible exception is a bit faster according to my scuffed testing.
        try {
            return m_registry.at(key);
        }
        catch (std::out_of_range &) {
            fmt::print(fg(fmt::color::yellow), "[{}] WARN: Resource {} does not exist\n", m_name, key);
            return std::nullopt;
        }
    }

protected:
    robin_hood::unordered_map<std::string, std::shared_ptr<T>> m_registry;

private:
    std::string m_name;
};

} // namespace Registries
