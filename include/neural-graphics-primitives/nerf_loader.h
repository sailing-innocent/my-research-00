/**
 * @file nerf_loader.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <neural-graphics-primitives/bounding_box.cuh>
#include <neural-graphics-primitives/common.h>

#include <vector>

RES_NAMESPACE_BEGIN

// how much to scale the scene by vs the original nerf dataset
static constexpr float NERF_SCALE = 0.33f;

struct TrainingImageMetadata {
    // Camera intrinstics and additional data associated with NeRF training image
    // the memory to back the pixels and rays is held by GPUMemory objects in the NerfDataset and copied here
    cosnt void* pixels = nullptr;
}

struct NerfDataset {

}

// NerfDataset load_nerf(const std::vector<filesystem::path>)
// NerfDataset create_empty_nerf_dataset

RES_NAMESPACE_END