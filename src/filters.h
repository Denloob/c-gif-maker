#ifndef FILTERSH
#define FILTERSH

#ifndef CV_IGNORE_DEBUG_BUILD_GUARD
#define CV_IGNORE_DEBUG_BUILD_GUARD
#endif /* ifndef CV_IGNORE_DEBUG_BUILD_GUARD */

#include "input.h"
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgcodecs/imgcodecs_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <stdio.h>

// this is the default in the cpp lib,
// and also the first 0 means sigma1
// will be auto calculated and sigma2
// is doesn't matter what is ignored in
// gaussian blur.
#define FILTER_BLUR_GAUSSIAN_SIGMA 0, 0

// In case of gaussian blur, setting
// size2=0, (as the default and the docs
// suggested) will result in it being
// set to value of size1
#define FILTER_BLUR_GAUSSIAN_SIZE2 0

// Default values + means they will be calculated based on sigma.
#define FILTER_SHARPEN_GAUSSIAN_SIZE 0, 0
// Default + not used for gaussian blur
#define FILTER_SHARPEN_GAUSSIAN_SIGMA2 0
// We just want to add back to the blurred image to sharpen, no need for gama
#define FILTER_SHARPEN_WEIGHTED_GAMMA 0
// In the range of about recommended `amount` by wikipedia
// @see https://en.wikipedia.org/wiki/Unsharp_masking#Digital_unsharp_masking
#define FILTER_SHARPEN_WEIGHTED_ALPHA 1.5
// The above comments applies to this too.
#define FILTER_SHARPEN_WEIGHTED_BETA -0.5

// This is here because as it turns out VS does some strange C/CPP
// voodoo magic, so cvGetSize doesn't work..
#define SIMPLE_CV_GET_SIZE(img) cvSize(img->width, img->height)

#define CREATE_IMAGE_WITH_PROPERTIES_OF(img)                                   \
    cvCreateImage(SIMPLE_CV_GET_SIZE(img), img->depth, img->nChannels)

#define CREATE_1D_IPLIMAGE_WITH_PROPERTIES_OF(img)                             \
    cvCreateImage(SIMPLE_CV_GET_SIZE(img), img->depth, 1)


#define FILTERS_INPUT_CONFIG_FORMAT_STR                                        \
    "Please enter the %s strength%s: "
#define FILTERS_INPUT_CONFIG_MIN_NUMBER 1

typedef struct FilterSaturateConfig
{
    double saturation_strength;
} FilterSaturateConfig;

typedef struct FilterBlurConfig
{
    int blur_strength;
} FilterBlurConfig;

typedef struct FilterSharpenConfig
{
    double sharpen_strength;
} FilterSharpenConfig;

typedef union FilterConfig
{
    FilterBlurConfig blur_config;
    FilterSharpenConfig sharpen_config;
    FilterSaturateConfig saturate_config;
} FilterConfig;

typedef IplImage *(*FilterFunction)(const IplImage *, const FilterConfig *);

enum FilterConfigType
{
    FILTER_CONFIG_TYPE_NONE,
    FILTER_CONFIG_TYPE_BLUR,
    FILTER_CONFIG_TYPE_SHARPEN,
    FILTER_CONFIG_TYPE_SATURATE,
};

extern const char *filter_names[];

extern const FilterFunction filter_functions[];

extern const enum FilterConfigType filter_types[];

#define FILTERS_MENU_SIZE                                                      \
    (sizeof(filter_functions) / sizeof(filter_functions[0]))

/**
 * @brief Prints the filter menu.
 */
void filters_menu_print();

/**
 * @brief Prompts the user to choose an option from the filter menu after
 *  displaying it.
 *
 * @return User's choice.
 */
unsigned long filters_menu_input_index();

/**
 * @brief Inputs the config from stdin based on it's type.
 *
 * @param config_type The type of config.
 * @param config_out The config to set. (Must be pre-allocated).
 */
void filters_input_config(enum FilterConfigType config_type,
                          FilterConfig *config_out);

/**
 * @brief Doesn't apply any filter.
 *
 * @param img The image to "apply the filter to" (aka do nothing with).
 * @param config The filter configuration. (Not used).
 * @return Copy of the image.
 */
IplImage *filters_none(const IplImage *img, const FilterConfig *config);

/**
 * @brief Converts the given image to grayscale.
 *
 * @param img The image to convert.
 * @param config The filter configuration. (Not used).
 * @return The converted image. (Newly allocated)
 */
IplImage *filters_grayscale(const IplImage *img, const FilterConfig *config);

/**
 * @brief Blur the given image.
 *
 * @param img The image to blur.
 * @param config The filter configuration. (FilterBlurConfig)
 * @return The blurred image. (Newly allocated)
 */
IplImage *filters_blur(const IplImage *img, const FilterConfig *config);

/**
 * @brief Sharpens the given image.
 *
 * @param img The image to sharpen.
 * @param config The filter configuration. (FilterSharpenConfig)
 * @return The sharpened image. (Newly allocated)
 */
IplImage *filters_sharpen(const IplImage *img, const FilterConfig *config);

/**
 * @brief Saturate the given image.
 *
 * @param img The image to saturate.
 * @param config The filter configuration. (FilterSaturateConfig)
 * @return The saturated image. (Newly allocated)
 */
IplImage *filters_saturate(const IplImage *img, const FilterConfig *config);

#endif /* FILTERSH */
