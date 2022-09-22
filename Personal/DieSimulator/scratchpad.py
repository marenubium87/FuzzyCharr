import simulator as sim

sim.Simulator.modify_dice(8, '+', 5)
sim.Simulator.perform_sim()
sim.Simulator.sanitize_outcomes()