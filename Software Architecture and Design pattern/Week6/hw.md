# Homework 6
## 2017141493004 常家奇

### The abstract common services tactic is intended to reduce coupling, but it also might reduce cohesion. Why?

> 使用抽象通用服务确实可以降低耦合,但使用抽象通用服务策略是将模块的共性抽象出来成一个抽象模块,对于每个模块特有属性的支持会变少,所以降低了内聚.

### Write a set of concrete scenarios for performance using each of the possible responses in the general scenario

Source | Stimulus | Artifact | Environment | Response | Response Measure
-------|----------|----------|-------------|----------|-----------------
Users | Initiate Transacations | System | Normal Operation | Transactions are processed | Average Latency of Two Seconds

