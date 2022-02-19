// queue.c file

//////////////////////////////////////////////
// TIMER QUEUE
void update_queue_times(TQE *q, int offset) {


}

int enqueue_timer(TQE **queue, TQE *p)
{
    TQE *q = *queue;
    int relativeTimeOffset = q -> time;

    if (q == 0)
    {
        *queue = p;
        p->next = 0;
        return 0;
    }

    // if queue -> time = 5, and insertin p -> 10
    // [1, 5] and want to insert [2, 10]
    // this says [2, 10] -> [1, 5]
    if ((*queue)->time > p->time)
    {
        (*queue)->time = (*queue)->time - p-> time;
        p->next = *queue;
        *queue = p;
        return 0;
    }
    p -> time = p -> time - relativeTimeOffset;
    while (q->next && p->time >= q->next->time)
    {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;
    p -> next -> time = p -> next -> time - p -> time;

}

TQE *qdequeue(TQE **queue)
{
    TQE *p = *queue;
    if (p)
        *queue = p->next;
    return p;
}

/////////////////////////////////////////////////

void removeprocess(PROC *p)
{
    PROC *parent = p->parent;
    if (parent->child == p)
    {
        if (p->sibling == 0)
            parent->child = 0;
        else
        {
            parent->child = p->sibling;
        }
    }
    else
    {
        PROC *pchild = parent->child;
        while (pchild->sibling != p)
        {
            pchild = pchild->sibling;
        }
        pchild->sibling = pchild->sibling->sibling;
    }

    p->parent = 0;
    p->sibling = 0;
    p->child = 0;
    p->ppid = 0;
}

void printsibings(PROC *p)
{
    printf("\n         |\n         ");
    while (p)
    {
        printf("P%d -> ", p->pid);
        p = p->sibling;
    }
    printf("NULL\n\n");
}

void printtree(PROC *p)
{

    if (p == 0)
        return;

    printf("Parent: \tP%d:", p->pid);
    if (p->child == 0 && p->sibling == 0)
    {
        printf(" no children or siblings\n", p->pid);
        return;
    }
    else if (p->child == 0)
    {
        printf(" no children\n");
    }
    else
    {
        printsibings(p->child);
    }
    printtree(p->sibling);
    if (p->child != 0)
    {
        printf("Press Enter To Continue:\n");
        kgetc();
    }
    printtree(p->child);
}

int enqueue(PROC **queue, PROC *p)
{
    PROC *q = *queue;
    if (q == 0)
    {
        *queue = p;
        p->next = 0;
        return 0;
    }
    if ((*queue)->priority < p->priority)
    {
        p->next = *queue;
        *queue = p;
        return 0;
    }
    while (q->next && p->priority <= q->next->priority)
    {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;
}

PROC *dequeue(PROC **queue)
{
    PROC *p = *queue;
    if (p)
        *queue = p->next;
    return p;
}

int printQ(PROC *p)
{
    kprintf("readyQueue = ");
    while (p)
    {
        kprintf("[%d%d]->", p->pid, p->priority);
        p = p->next;
    }
    kprintf("NULL\n");
}

int printSleepList(PROC *p)
{
    printf("sleepList   = ");
    while (p)
    {
        kprintf("[%devent=%d]->", p->pid, p->event);
        p = p->next;
    }
    kprintf("NULL\n");
}

int printList(char *name, PROC *p)
{
    kprintf("%s = ", name);
    while (p)
    {
        kprintf("[%d%d]->", p->pid, p->priority);
        p = p->next;
    }
    kprintf("NULL\n");
}
