// Copyright (C) 2018-2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <map>

#include "openvino/pass/manager.hpp"
#include "openvino/pass/serialize.hpp"
#include "openvino/core/attribute_visitor.hpp"
#include "openvino/core/attribute_adapter.hpp"
#include "openvino/core/enum_names.hpp"

#include "utils/model_comparator.hpp"

namespace ov {
namespace util {

class ReadAttributes : public ov::AttributeVisitor {
    std::map<std::string, std::string> attributes_map;
    std::map<std::string, std::shared_ptr<ov::Model>> model_attributes_map;

    template <typename Container>
    std::string join(const Container& c, const char* glue = ", ") {
        std::stringstream oss;
        const char* s = "";
        for (const auto& v : c) {
            oss << s << v;
            s = glue;
        }
        return oss.str();
    }

    template <typename T>
    std::string create_atribute_list(ov::ValueAccessor<std::vector<T>>& adapter) {
        return join(adapter.get());
    }

public:
    ReadAttributes() = default;

    std::map<std::string, std::string> get_attributes_map() { return attributes_map; }
    std::map<std::string, std::shared_ptr<ov::Model>> get_model_attributes_map() { return model_attributes_map; }
    
    void on_adapter(const std::string& name, ov::ValueAccessor<void>& adapter) override {
        attributes_map.insert({ name, "" });
    }

    void on_adapter(const std::string& name, ov::ValueAccessor<bool>& adapter) override {
        attributes_map.insert({ name, std::to_string(adapter.get()) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<std::string>& adapter) override {
        attributes_map.insert({ name, adapter.get() });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<int64_t>& adapter) override {
        attributes_map.insert({ name, std::to_string(adapter.get()) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<double>& adapter) override {
        attributes_map.insert({ name, std::to_string(adapter.get()) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<std::vector<int>>& adapter) override {
        attributes_map.insert({ name, create_atribute_list(adapter) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<std::vector<int64_t>>& adapter) override {
        attributes_map.insert({ name, create_atribute_list(adapter) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<std::vector<uint64_t>>& adapter) override {
        attributes_map.insert({ name, create_atribute_list(adapter) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<std::vector<float>>& adapter) override {
        attributes_map.insert({ name, create_atribute_list(adapter) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<std::vector<std::string>>& adapter) override {
        attributes_map.insert({ name, create_atribute_list(adapter) });
    }
    void on_adapter(const std::string& name, ov::ValueAccessor<std::shared_ptr<ov::Model>>& adapter) override {
        model_attributes_map.insert({ name, adapter.get() });
    }
};

}  // namespace util
}  // namespace ov
