void transform(int *from, int *to)
{
    if(to - from == 1)
        return;
    int *mid = from + (to - from) / 2;
    transform(from, mid);
    transform(mid, to);
    for(int i = 0; i < mid - from; i++)
        *(mid + i) += *(from + i);
}

void inverse(int *from, int *to)
{
    if(to - from == 1)
        return;
    int *mid = from + (to - from) / 2;
    inverse(from, mid);
    inverse(mid, to);
    for(int i = 0; i < mid - from; i++)
        *(mid + i) -= *(from + i);
}