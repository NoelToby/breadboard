// Copyright 2015 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "event/graph_loader.h"

#include <string>

#include "event/event_system.h"
#include "event/graph.h"

namespace fpl {
namespace event {

Graph* GraphLoader::LoadGraph(const char* filename) {
  // Have we loaded this flatbuffer already?
  auto iter = loaded_graphs_.find(filename);
  if (iter != loaded_graphs_.end()) {
    // If so, return the cached graph.
    return iter->second.get();
  } else {
    // If not, load it and return it.
    std::string data;
    if (!load_file_callback_(filename, &data)) {
      return nullptr;
    }
    event::Graph* graph = new event::Graph();
    if (!ParseData(event_system_, graph, &data)) {
      return nullptr;
    }
    iter->second.reset(graph);
    return graph;
  }
}

}  // event
}  // fpl
