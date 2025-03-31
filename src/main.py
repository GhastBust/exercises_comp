from g_raph import g_raph
import numpy as np

from putils import units

c = 1
Mn = 938.565
p0 = Mn * 0.16
P0 = p0 * c**2
hc = 197.327
G = hc * 6.67259e-45

R0 = np.sqrt( P0 /4 /np.pi /G /p0**2 )
M0 = R0 *P0 /G /p0

MeVc2_to_solar = 1.79e-30 * 5.02785e-31


def main():


 
    # g_raph.graph_solution_ctn_sqrt()
    
    g_raph.graph_iterations_methods()

    # g_raph.graph_star_radius_mass()

    # print("R0 = ", R0 * 1e-18, "km")
    # print("M0 = ", M0 * MeVc2_to_solar, "Mo")


if __name__ == "__main__":
    main()
