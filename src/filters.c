#include "filters.h"

const char *filter_names[] = {
    "None", "Grayscale", "Blur", "Sharpen", "Saturate",
};

const FilterFunction filter_functions[] = {
    filters_none,    filters_grayscale, filters_blur,
    filters_sharpen, filters_saturate,
};

const enum FilterConfigType filter_types[] = {
    FILTER_CONFIG_TYPE_NONE,     FILTER_CONFIG_TYPE_NONE,
    FILTER_CONFIG_TYPE_BLUR,     FILTER_CONFIG_TYPE_SHARPEN,
    FILTER_CONFIG_TYPE_SATURATE,
};

void filters_menu_print()
{
    for (unsigned long i = 0; i < FILTERS_MENU_SIZE; i++)
    {
        printf(" [%lu] %s\n", i, filter_names[i]);
    }
}

unsigned long filters_menu_input_index()
{
    unsigned long choice =
        input_choice_max(FILTERS_MENU_SIZE, filters_menu_print,
                         "Choose a filter\n", "Invalid choice, try again:\n");

    return choice;
}

void filters_input_config(enum FilterConfigType config_type,
                          FilterConfig *config_out)
{
    switch (config_type)
    {
        case FILTER_CONFIG_TYPE_NONE:
            break;
        case FILTER_CONFIG_TYPE_BLUR:
            do
            {
                printf(FILTERS_INPUT_CONFIG_FORMAT_STR, "blur", " (integer larger or equal to 1)");
                scanf("%d", &config_out->blur_config.blur_strength);
                if (config_out->blur_config.blur_strength % 2 == 0 &&
                    config_out->blur_config.blur_strength > 0)
                {
                    // Make it odd for the Gaussian kernel.
                    config_out->blur_config.blur_strength++;
                }
            } while (config_out->blur_config.blur_strength <
                     FILTERS_INPUT_CONFIG_MIN_NUMBER);
            break;
        case FILTER_CONFIG_TYPE_SHARPEN:
            do
            {
                printf(FILTERS_INPUT_CONFIG_FORMAT_STR, "sharpen",
                       " (any number larger or equal to 1)");
                scanf("%lf", &config_out->sharpen_config.sharpen_strength);
            } while (config_out->sharpen_config.sharpen_strength <
                     FILTERS_INPUT_CONFIG_MIN_NUMBER);
            break;
        case FILTER_CONFIG_TYPE_SATURATE:
            printf(FILTERS_INPUT_CONFIG_FORMAT_STR, "saturation",
                   "");
            scanf("%lf", &config_out->saturate_config.saturation_strength);
            break;
    }
}

// The unused variable is expected!
IplImage *filters_none(const IplImage *img, const FilterConfig *_)
{
    return cvCloneImage(img);
}

// The unused variable is expected!
/*
 * @see https://docs.opencv.org/3.4/de/d25/imgproc_color_conversions.html */
IplImage *filters_grayscale(const IplImage *img, const FilterConfig *_)
{
    IplImage *grayscale_img =
        CREATE_1D_IPLIMAGE_WITH_PROPERTIES_OF(img);
    // Uses the `Y = 0.299 * R + 0.587 * G + 0.114 * B` formula
    cvCvtColor(img, grayscale_img, CV_BGR2GRAY);

    return grayscale_img;
}

IplImage *filters_blur(const IplImage *img, const FilterConfig *config)
{
    IplImage *blur_img = CREATE_IMAGE_WITH_PROPERTIES_OF(img);

    cvSmooth(img, blur_img, CV_GAUSSIAN, config->blur_config.blur_strength,
             FILTER_BLUR_GAUSSIAN_SIZE2, FILTER_BLUR_GAUSSIAN_SIGMA);

    return blur_img;
}

/*
 * @credit https://stackoverflow.com/a/4993701/16586000
 */
IplImage *filters_sharpen(const IplImage *img, const FilterConfig *config)
{
    double sharpen_strength = config->sharpen_config.sharpen_strength;
    IplImage *sharpened_img = CREATE_IMAGE_WITH_PROPERTIES_OF(img);

    cvSmooth(img, sharpened_img, CV_GAUSSIAN, FILTER_SHARPEN_GAUSSIAN_SIZE,
             sharpen_strength, FILTER_SHARPEN_GAUSSIAN_SIGMA2);

    cvAddWeighted(img, FILTER_SHARPEN_WEIGHTED_ALPHA, sharpened_img,
                  FILTER_SHARPEN_WEIGHTED_BETA, FILTER_SHARPEN_WEIGHTED_GAMMA,
                  sharpened_img);

    return sharpened_img;
}

IplImage *filters_saturate(const IplImage *img, const FilterConfig *config)
{
    IplImage *img_clone = cvCloneImage(img);
    IplImage *saturated_img = CREATE_IMAGE_WITH_PROPERTIES_OF(img);

    CvScalar saturation_value =
        cvScalarAll(config->saturate_config.saturation_strength);

    // channels=1 because we are extracting channels, so each one of them will
    // have 1
    IplImage *hue_channel = CREATE_1D_IPLIMAGE_WITH_PROPERTIES_OF(img);
    IplImage *saturation_channel = CREATE_1D_IPLIMAGE_WITH_PROPERTIES_OF(img);
    IplImage *value_channel = CREATE_1D_IPLIMAGE_WITH_PROPERTIES_OF(img);

    cvCvtColor(img, img_clone, CV_BGR2HSV);
    cvSplit(img_clone, hue_channel, saturation_channel, value_channel, NULL);

    cvAddS(saturation_channel, saturation_value, saturation_channel, NULL);

    cvMerge(hue_channel, saturation_channel, value_channel, NULL,
            saturated_img);

    cvReleaseImage(&hue_channel);
    cvReleaseImage(&saturation_channel);
    cvReleaseImage(&value_channel);
    cvReleaseImage(&img_clone);

    cvCvtColor(saturated_img, saturated_img, CV_HSV2BGR);

    return saturated_img;
}
