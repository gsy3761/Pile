# 单源最短路问题

## 定义

最短路问题是:

>给定一个有权图$G=(V,E)$
>
>对于图上的某一特定点对$(u,v)$
>
>寻找一条路径,使得这条路径的权值和最小

这里的权值既可以指路程,也可以指油耗,时间,等等会随路程线性累加,且我们希望其最小的量

## 变种

1. 单源最短路:求从一个点出发到其他所有节点的最短路

1. 单目的地最短路:到达某一特定目的地的最短路

1. 所有点对的最短路:任意节点对之间的最短路问题(将于Section25详细讨论)

## 性质

1. ***两个节点间的最短路也是这条最短路上的其他节点对的最短路***

    或者说,最短路问题满足最优子结构

2. ***具有负权的边是可以接受的,但是具有负权的环不行***

3. ***权值为正的环路也不行***

4. ***因此,任何单源最短路的结果应当形成一棵最短路树***

## 计算

### 向节点附加的属性

1. 当前距离

    对于每一个节点$v$,我们记录一个值$v.d$,为对 源点到其最短路的权值 的上界 的估计

    随着计算的进行,这个估计会不断变小,趋向于实际的最小权值

2. 前驱节点

    前面提到,最短路径组成一棵以源点为根的树,为了最后能输出计算得到的最短路而不仅仅是最小权,我们为每个节点记录它在树上的父节点,为$v.\pi$

### 数据存储及初始化

在这里,我们假定

1. 所有节点存储在一个数组中(支持$O(1)$的随机访问)

2. 边存储在邻接链表中,权值作为边的性质,与边存在一起

每次开始运算前我们调用以下函数来进行初始化节点的属性

```python
def iniSingleSource(G,s):
    for v in G.V:
        v.d = INF
        v.PI = NULL
    s.d = 0
```
### 松弛

随着计算的进行,我们需要不断地改善每一个节点的$v.d$

其具体方法如下:  
我们随便找一个其他的节点$u$满足$(u,v) \in G.E$  
比较$u.d + (u.v).\omega$和$v.d$
如果可以的话就减小$v.d$并且修改$v.\pi$

```python
def relax(u,v,w):
    if u.d + w(u,v) < v.d:#w是一个能够返回该边的权值的函数,如果这条边不存在,应当返回正无穷
        v.d = u.d + (u,v).w
        v.PI = u

def relax(e):
    if e.u.d + e.w < e.v.d:
        e.v.d = e.u.d + e.w
        e.v.PI = e.u
```

### Bellman-Ford

Bellman-Ford算法是一种朴素而暴力的最短路算法,在它的每次操作中,都对所有存在的边进行松弛操作,最多尝试$\mid G.V \mid - 1$次,代码如下

```python
def BellmanFord(G,s):
    iniSingleSource(G,s)
    for i in range(G.V.size()-1):
        for e in G.E:
            relax(e)
    for e in G.E:
        if e.u.d + e.w < e.v.d:
            return False
    return True
```

不难看出,该算法的复杂度为$O(V\cdot E)$,在稠密图中,会恶化到$O(V^3)$,因此该算法虽然简单易懂,但是在实际应用中是不够的,当然,还存在特例-有向无环图,对于这种图,适当的松弛顺序可以把复杂度降低到$O(V + E)$,但是其实际意义有限,不提了.

### Dijkstra

不难看出,B-F算法在尝试松弛上做了不少无用功,反复尝试松弛已经最优的边以及尝试松弛还没有触及,即源点的距离仍为正无穷的边.

为了节约时间,我们要保存一个集合,记录那些已经确定不能更优的点.然后不断的扩大这个集合,直到不能继续.

```python
def Dijkstra(G,s):
    iniSingleSource(G,s)
    Q = G.V
    S = set()#之前提到的集合
    while not Q.empty():
        n = Q[0]
        for u in Q:
            if u.d < n.d:
                n = u
        Q.remove(n)
        S += {n}
        for e in G.Adj[n]:
            relax(e)
```

这个算法每次选择预期距离最近的点加入集合,这是明显的贪心,这个算法并非完全正确,若存在负权 ***边*** 就可能出错,但是以此为代价,我们把复杂度降低至$O(V^2+E)$

但这不是优化的终点,由于我们每次贪心都贪最小的,我们自然会想到优先队列.

引入优先队列后,我们将复杂度降到了$O((V+E)\cdot Log(V))$,同时也看到了解决其缺陷的方法,具体见本目录下的SFPFAorDijkstra内的说明