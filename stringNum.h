#include <linux/device.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>

typedef struct {
    char *number;
    unsigned int size;
} stringNum;

void reverse_str(char *str, int size)
{
    for (int i = 0; i < (size >> 1); i++) {
        char tmp = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = tmp;
    }
}

stringNum *stringNumInit(int size)
{
    stringNum *new = kmalloc(sizeof(*new), GFP_KERNEL);
    char *tmp = kmalloc(sizeof(char) * (size + 1), GFP_KERNEL);

    memset(tmp, '\0', size + 1);
    new->number = tmp;
    new->size = 0;

    return new;
}

void stringNumFree(stringNum *data)
{
    kfree(data->number);
    kfree(data);
}

int stringToData(char *str, stringNum *data)
{
    int size = strlen(str);

    memset(data->number, '\0', size + 1);
    memcpy(data->number, str, size);
    data->size = size;

    return size;
}

void stringAdd(stringNum *a, stringNum *b, stringNum *result)
{
    char *num_a, *num_b;
    int size_a, size_b;
    int i, sum, carry = 0;

    if (a->size < b->size) {
        num_a = b->number;
        size_a = b->size;
        num_b = a->number;
        size_b = a->size;
    } else {
        num_a = a->number;
        size_a = a->size;
        num_b = b->number;
        size_b = b->size;
    }

    reverse_str(num_a, size_a);
    reverse_str(num_b, size_b);

    char *buf = kmalloc(sizeof(char) * (size_a + 2), GFP_KERNEL);

    for (i = 0; i < size_b; i++) {
        sum = (num_a[i] - '0') + (num_b[i] - '0') + carry;
        buf[i] = '0' + sum % 10;
        carry = sum / 10;
    }

    for (i = size_b; i < size_a; i++) {
        sum = (num_a[i] - '0') + carry;
        buf[i] = '0' + sum % 10;
        carry = sum / 10;
    }

    if (carry) {
        buf[i] = '1';
        i++;
    } else {
        buf[i] = 0;
    }
    reverse_str(buf, i);

    reverse_str(num_a, size_a);
    reverse_str(num_b, size_b);

    memcpy(result->number, buf, i);
    result->size = strlen(result->number);
    kfree(buf);
}