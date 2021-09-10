/*
Pop (queue)
    if queue is empty
        do nothing

    read_idx++
    rea_idx %= capacity
    size--

Push (queue, data)
    if queue is full
        do nothing

    arr[(read_idx + size) % capacity] = data
    size++
*/
