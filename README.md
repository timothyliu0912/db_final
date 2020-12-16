# DB-Final

## structure

### Node

* _id: binary (md5(word))
* word: str
* count: int
* sound: List[str]
* next_edges: List[Edge*]
* prev_edges: List[Edge*]

### Edge

* _id: int binary (md5(prev_node->word) + md5(next_node->word))
* prev_node: Node*
* next_node: Node*
* weight: float, (PMI)
<!-- * factor -->
