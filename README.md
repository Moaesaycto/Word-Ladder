# **Word Ladder**

**Type:** Algorithm / CLI · **Tech Stack:** C++ (STL) · **Status:** Completed

## **Overview:**
Finds all shortest word ladders between a start and end word using a lexicon and **breadth-first search (BFS)**.

## **Examples:**
Here is a word ladder connecting "code" to "data".

```txt
code -> cade -> cate -> date -> data
```

Many word ladders will have multiple solutions, such as connecting "work" to "play".

```txt
work fork form foam flam flay play
work pork perk peak pean plan play
work pork perk peak peat plat play
work pork perk pert peat plat play
work pork porn pirn pian plan play
work pork port pert peat plat play
work word wood pood plod ploy play
work worm form foam flam flay play
work worn porn pirn pian plan play
work wort bort boat blat plat play
work wort port pert peat plat play
work wort wert pert peat plat play
```

## **How it works:**

* Builds adjacency by single-letter mutations present in the lexicon.
* Runs BFS from the start word, recording parents to reconstruct paths of **minimal length only**.
* Returns a `std::vector<std::vector<std::string>>` of ladders.

## **Features:**

* Multiple shortest solutions returned deterministically (sorted).
* Input validation (equal lengths, words in lexicon, reachable checks).
* Optional pruning (visited per level) to avoid revisiting longer paths.
