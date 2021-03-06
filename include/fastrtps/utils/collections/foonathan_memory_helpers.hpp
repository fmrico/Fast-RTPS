// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/**
 * @file foonathan_memory_helpers.hpp
 *
 */

#ifndef FASTRTPS_UTILS_COLLECTIONS_FOONATHAN_MEMORY_HELPERS_HPP_
#define FASTRTPS_UTILS_COLLECTIONS_FOONATHAN_MEMORY_HELPERS_HPP_

#include <foonathan/memory/memory_pool.hpp>

#include "ResourceLimitedContainerConfig.hpp"

namespace eprosima {
namespace fastrtps {

/**
 * A helper to calculate the block size of a memory pool given the side of the node and
 * a resource limits configuration.
 *
 * @tparam MemoryPool memory_pool specialization
 *
 * @param node_size   Size of the node for the memory pool
 * @param limits      Resource limits configuration of the container
 *
 * @return the block size to pass to the memory pool constructor
 */
template <typename MemoryPool>
std::size_t memory_pool_block_size(
        std::size_t node_size,
        const ResourceLimitedContainerConfig& limits)
{
    size_t num_elems = limits.increment > 0 ? limits.initial : limits.maximum;
    if (num_elems < 1u)
    {
        num_elems = 1u;
    }

    // Make room for debug fence
    num_elems += 2u;

    return node_size * num_elems       // Room for elements
        + MemoryPool::min_node_size    // Room for free_list nodes
        + 16u;                         // Additional fence space
}

}  // namespace fastrtps
}  // namespace eprosima

#endif /* FASTRTPS_UTILS_COLLECTIONS_FOONATHAN_MEMORY_HELPERS_HPP_ */
