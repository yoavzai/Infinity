
struct circ_buff
{
    int* arr;
    int capacity;
    int write_idx;
    int read_idx;
};

struct circ_buff circ_buff;

void CBCreate(int* arr, int capacity)
{
    circ_buff.arr = arr;
    circ_buff.capacity = capacity;
    circ_buff.write_idx = 0;
    circ_buff.read_idx = 0;
}

void CBWrite(int value)
{
    circ_buff.arr[circ_buff.write_idx] = value;
    circ_buff.write_idx++;

    if (circ_buff.write_idx == circ_buff.capacity)
    {
        circ_buff.write_idx = 0;
    }
}

int CBRead()
{
    int value = circ_buff.arr[circ_buff.read_idx];
    circ_buff.read_idx++;

    if (circ_buff.read_idx == circ_buff.capacity)
    {
        circ_buff.read_idx = 0;
    }

    return value;
}