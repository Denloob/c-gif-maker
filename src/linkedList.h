#ifndef LINKEDLISTH
#define LINKEDLISTH

#include "frame.h"
#include "input.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define FRAME_LIST_DISPLAY_NAME_FIELD_NAME "Name"
#define FRAME_LIST_DISPLAY_DURATION_FIELD_NAME "Duration"
#define FRAME_LIST_DISPLAY_PATH_FIELD_NAME "Path"

typedef struct FrameNode
{
    Frame *frame;
    struct FrameNode *next;
} FrameNode;

/**
 * @brief Creates a new node with the given frame.
 *
 * @param frame The frame to create the node with.
 * @return A pointer to the new node.
 */
FrameNode *frame_node_create(Frame *frame);

/**
 * @brief Cleans up the node.
 *
 * @param node The node to clean up.
 */
void frame_node_cleanup(FrameNode *node);

/**
 * @brief Returns the length of the list.
 *
 * @param list The list to get the length of.
 * @return The length of the list.
 */
unsigned int frame_list_length(FrameNode *list);

/**
 * @brief Appends the given frame to the end of the list.
 *
 * @param list_ptr A pointer to the list.
 * @param frame The frame to append.
 * @return A pointer to the new frame.
 */
void frame_list_append(FrameNode **list_ptr, Frame *frame);

/**
 * @brief Appends a frame to the end of the list using data from stdin.
 *        Makes sure that a frame with the same name does not already exist.
 *
 * @param list_ptr A pointer to the list.
 * @return A pointer to the new frame.
 */
void frame_list_append_stdin(FrameNode **list_ptr);

/**
 * @brief Cleans up the list.
 *
 * @param list The list to clean up.
 */
void frame_list_cleanup(FrameNode *list);

/**
 * @brief Pops out the node at the given index.
 *
 * @param list_ptr A pointer to the list.
 * @param index The index of the frame to pop.
 * @param out The frame that was popped.
 * @return True if the frame was popped, false otherwise.
 */
bool frame_list_pop(FrameNode **list_ptr, unsigned int index, FrameNode **out);

/**
 * @brief Removes a frame from the list.
 *
 * @param list_ptr A pointer to the list.
 * @param index The index of the frame to remove.
 * @return True if the frame was removed, false otherwise.
 */
bool frame_list_remove(FrameNode **list_ptr, unsigned int index);

/**
 * @brief Finds a frame by name
 *
 * @param list The list to search in.
 * @param name The name of the frame to find.
 * @param out Index of the frame.
 * @return True if the frame was found, false otherwise.
 */
bool frame_list_find_by_name(FrameNode *list, char *name, unsigned int *out);

/**
 * @brief Gets a frame by index.
 *
 * @param list A pointer to the list.
 * @param index The index of the frame to get.
 * @param out The node at the given index.
 * @return True if the frame was found, false otherwise.
 */
bool frame_list_get(FrameNode *list, unsigned int index, FrameNode **out);

/**
 * @brief Inserts a frame into the list at the given index.
 *
 * @param list_ptr A pointer to the list.
 * @param index The index to insert the frame at.
 * @param node The frame to insert.
 * @return True if the frame was inserted, false otherwise.
 */
bool frame_list_insert(FrameNode **list_ptr, unsigned int index,
                       FrameNode *node);

/**
 * @brief Moves a frame in the list from index to target_index
 *
 * @param list_ptr A pointer to the list.
 * @param index The index of the frame to move.
 * @param target_index The index of the frame to move to.
 * @return True if the frame was moved, false otherwise.
 */
bool frame_list_move_frame(FrameNode **list_ptr, unsigned int index,
                           unsigned int target_index);

/**
 * @brief Applies the given method to each frame in the list.
 *
 * @param list The list to apply the modifier to.
 * @param method The method to apply.
 */
void frame_list_apply(FrameNode *list, FrameMethod method);

/**
 * @brief Sets the duration of a each frame to the given one.
 *
 * @param list The list to set the duration of.
 * @param duration The duration to set.
 */
void frame_list_set_duration(FrameNode *list, unsigned int duration);
// Sadly, there is no way to have closures in C, which means it's the only way
// to do something like this.

/**
 * @brief Displays the list.
 *
 * @param list The list to display.
 */
void frame_list_display(FrameNode *list);

/**
 * @brief Reverses the list.
 *
 * @param list_ptr A pointer to the list.
 */
void frame_list_reverse(FrameNode **list_ptr);

/**
 * @brief Recursive implementation for the reverse function.
 *          Reverses the list.
 *
 * @param head The head of the list to reverse.
 * @return The new head after reverse.
 */
FrameNode *frame_list_reverse_impl(FrameNode *head);

#endif /* ifndef LINKEDLISTH */
