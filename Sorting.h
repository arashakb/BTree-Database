
vector<Node *> bubbleSort(vector<Node *> arr)
{
    int i, j;
    for (i = 0; i < arr.size() - 1; i++)

        for (j = 0; j < arr.size() - i - 1; j++)
            if (arr[j]->data > arr[j + 1]->data)
            {
                Node *tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
    return arr;
}