#include "linkedList.h"

FrameNode *frame_node_create(Frame *frame)
{
    FrameNode *node = malloc(sizeof(FrameNode));

    node->frame = frame;
    node->next = NULL;

    return node;
}

unsigned int frame_list_length(FrameNode *list)
{
    unsigned int length = 0;

    while (list)
    {
        list = list->next;

        length++;
    }

    return length;
}

void frame_list_append(FrameNode **list_ptr, Frame *frame)
{
    FrameNode *curr = *list_ptr;

    if (!curr)
    {
        *list_ptr = frame_node_create(frame);
        return;
    }

    frame_list_append(&curr->next, frame);
}

void frame_list_append_stdin(FrameNode **list_ptr)
{
    Frame *frame = frame_create_stdin();
    unsigned int tmp = 0;

    if (!frame)
    {
        return;
    }

    while (frame_list_find_by_name(*list_ptr, frame->name, &tmp))
    {
        puts("The name is already taken, please enter another name");
        free(frame->name);
        frame->name = input();
    }

    frame_list_append(list_ptr, frame);
}

void frame_node_cleanup(FrameNode *node)
{
    frame_cleanup(node->frame);
    free(node);
}

void frame_list_cleanup(FrameNode *list)
{
    if (!list)
    {
        return;
    }

    frame_list_cleanup(list->next);
    frame_node_cleanup(list);
}

bool frame_list_pop(FrameNode **list_ptr, unsigned int index, FrameNode **out)
{
    FrameNode *prev_node = NULL;
    FrameNode *node = *list_ptr;
    bool success = 0;

    // this code would be much easier to read with early returns..
    if (!node)
    {
        success = false;
    }
    else if (index == 0)
    {
        success = true;
        *list_ptr = node->next;
    }
    else if ((success = frame_list_get(*list_ptr, index - 1, &prev_node)))
    {
        node = prev_node->next;
        prev_node->next = node->next;
    }

    if (success)
    {
        *out = node;
    }

    return success;
}

bool frame_list_remove(FrameNode **list_ptr, unsigned int index)
{
    FrameNode *node = NULL;
    bool success = frame_list_pop(list_ptr, index, &node);

    if (success)
    {
        frame_node_cleanup(node);
    }

    return success;
}

bool frame_list_find_by_name(FrameNode *list, char *name, unsigned int *out)
{
    bool search_succeed = 0;

    if (!list)
    {
        return false;
    }

    if (!strcmp(list->frame->name, name))
    {
        *out = 0;
        return true;
    }

    search_succeed = frame_list_find_by_name(list->next, name, out);

    *out += 1;

    return search_succeed;
}

bool frame_list_get(FrameNode *list, unsigned int index, FrameNode **out)
{
    if (!list)
    {
        return false;
    }

    if (!index)
    {
        *out = list;
        return true;
    }

    return frame_list_get(list->next, index - 1, out);
}

bool frame_list_move_frame(FrameNode **list_ptr, unsigned int index,
                           unsigned int target_index)
{
    FrameNode *node = NULL;

    return frame_list_pop(list_ptr, index, &node) &&
           frame_list_insert(list_ptr, target_index, node);
}

bool frame_list_insert(FrameNode **list_ptr, unsigned int index,
                       FrameNode *node)
{
    FrameNode *next = NULL;
    FrameNode *prev = NULL;

    bool success = 0;

    // Again, early returns would make this much better.

    if (index == 0)
    {
        next = *list_ptr;
        *list_ptr = node;

        success = true;
    }
    else if ((success = frame_list_get(*list_ptr, index - 1, &prev)))
    {
        next = prev->next;
        prev->next = node;
    }

    if (success)
    {
        node->next = next;
    }

    return success;
}

void frame_list_apply(FrameNode *list, FrameMethod method)
{
    if (!list)
    {
        return;
    }

    method(list->frame);

    frame_list_apply(list->next, method);
}

void frame_list_set_duration(FrameNode *list, unsigned int duration)
{
    while (list)
    {
        list->frame->duration = duration;

        list = list->next;
    }
}

void frame_list_display(FrameNode *list)
{
    printf("\t\t%*s %*s %s\n", FRAME_DISPLAY_JUSTIFICATION,
           FRAME_LIST_DISPLAY_NAME_FIELD_NAME, FRAME_DISPLAY_JUSTIFICATION,
           FRAME_LIST_DISPLAY_DURATION_FIELD_NAME,
           FRAME_LIST_DISPLAY_PATH_FIELD_NAME);
    frame_list_apply(list, frame_display);
}

FrameNode *frame_list_reverse_impl(FrameNode *head)
{
    FrameNode *new_head = NULL;

    if (!head)
    {
        return NULL;
    }

    if (!head->next)
    {
        return head;
    }

    new_head = frame_list_reverse_impl(head->next);

    head->next->next = head;
    head->next = NULL;

    return new_head;
}

void frame_list_reverse(FrameNode **list_ptr)
{
    *list_ptr = frame_list_reverse_impl(*list_ptr);
}
