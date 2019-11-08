# Homework 5
## 2017141493004 常家奇


Source | Stimulus | Artifact | Environment | Response | Response Measure
-------|----------|----------|-------------|----------|-----------------
Heartbeat Monitor | Server unresponsive | Process | Normal Operation | Inform Operator Continue to Operate | No Downtime
Memory Monitor | Thread crash | Process | Normal Operation | Log the system status,Notify the crash system,kill the thread,recover the thread | No Downtime

exploit redundancy :

- Voting
  - Replication
  - Functional redundancy
  - Analytic redundancy
- Active redundancy
- Passive redundancy
- Spare
- Rollback
- State resynchronization

Not exploit redundancy :

- Ping/echo
- Monitor
- Heartbeat
- Time stamp
- Sanity checking
- Exception detection
  - System exceptions
  - The parameter fence
  - Parameter typing
  - TImeout
- Self-test
- Exception handling
- Software upgrade
- Removal from service
- Transactions
- Predictive model