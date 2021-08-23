void transform(int *from, int *to)
{
    if(to - from == 1)
        return;
    int *mid = from + (to - from) / 2;
    transform(from, mid);
    transform(mid, to);
    for(int i = 0; i < mid - from; i++)
    {
        int a = *(from + i);
        int b = *(mid + i);
        *(from + i) = a + b;
        *(mid + i) = a - b;
    }
}

void inverse(int *from, int *to) {
    transform(from, to);
    for (int *i = from; i < to; i++) (*i) /= (to-from);
}