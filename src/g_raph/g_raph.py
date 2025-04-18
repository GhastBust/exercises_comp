import putils
import csv
import numpy as np
from matplotlib import pyplot 
from os.path import join


import putils.graph


def extract(file):

    channels: list[list[float]] = []


    with open(file) as csvfile :
        
        reader = csv.reader(csvfile)
            
        for i, row in enumerate(reader):
            
            if i == 0: 
                for _ in row:
                    channels.append([])

            #* valida i risultati nella corrente riga
            try:
                
                for j, current_v in enumerate(row):
                    channels[j].append(float(current_v))
                    
            except ValueError:
                continue

    return channels


def graph_solution_ctn_sqrt():

    a = extract("data/ctn_sqrt.csv")

    ex = 300

    x = np.array(a[0][:-ex]) * 11.133474484828408
    y1 = a[1][:-ex]
    y2 = a[2][:-ex]

    fig = putils.graph.PFig(pyplot.figure(), "Risoluzione Grafica", "Energia [MeV]", "f(E)")

    fig.data(x, y1, label=r"$-\sqrt{\frac{e}{v-e}}$", shape=".", linestyle= "-")
    fig.data(x, y2, label=r"$\cot{\sqrt{v-e}}$", shape=".", linestyle= "-")
    
    fig.polish(save_name="solutions_ctn_sqrt", save_format="all", legend_position="lower left", show= True)


def graph_iterations_methods():

    a = extract("data/bisection.csv")
    bis = np.array(a[0])

    a = extract("data/newton-rapson.csv")
    nr = np.array(a[0])

    sol = 0.190408573835450875655341432704267102747 * 11.133474484828408

    bis = np.abs(bis - sol)
    nr  = np.abs(nr - sol) 

    # bis = np.log10(bis)
    # nr  = np.log10(nr)

    fig = putils.graph.PFig(pyplot.figure(), "Differenza tra approx. e soluzione", "Iterazioni", "Differenza")

    fig.data(np.arange(len(bis)), bis, label="Bisezione", shape=".", linestyle= "-")
    fig.data(np.arange(len(nr )), nr , label="Secanti", shape=".", linestyle= "-")

    axes = pyplot.gca()

    axes.set_yscale("log")

    fig.polish(save_name="bis-newrap", save_format="all", show=True)



def graph_star_radius_mass(): 

    files = [
        "gamma5-3.csv",
        "gamma4-3.csv",
        "gamma2.54.csv"
    ]

    labels = [ 
        r"$\Gamma = \frac{5}{3}$",
        r"$\Gamma = \frac{4}{3}$",
        r"$\Gamma = 2.54$"
    ]

    colors = [
        "red",
        "olivedrab",
        "blue",
    ]

    fig = putils.graph.PFig( pyplot.figure(), "Raggio e massa solare a confronto", "Raggio [Km]", r"Massa [$M_{\odot}$]")


    for (file, label, color) in zip(files, labels, colors):

        a = extract(join("data", file))

        r = np.array( a[0] )
        m = np.array( a[1] )

        fig.data(r, m, label=label, color= color, linestyle="-")

    axes = pyplot.gca()

    axes.set_xscale("log")
    axes.set_yscale("log")

    fig.polish()


def graph_rel_star_radius_mass(): 

    files = [
        "rel_gamma5-3.csv",
        "rel_gamma4-3.csv",
        "rel_gamma2.54.csv"
    ]

    labels = [ 
        r"$\Gamma = \frac{5}{3}$",
        r"$\Gamma = \frac{4}{3}$",
        r"$\Gamma = 2.54$"
    ]

    colors = [
        "red",
        "olivedrab",
        "blue",
    ]

    fig = putils.graph.PFig( pyplot.figure(), "Pressione e massa solare a confronto", "Raggio [km]", r"Massa [$M_{\odot}$]")


    for (file, label, color) in zip(files, labels, colors):

        a = extract(join("data", file))

        r = np.array( a[0] )
        m = np.array( a[1] )

        fig.data(r, m, label=label, color= color, linestyle="-")

    axes = pyplot.gca()

    axes.set_xscale("log")
    axes.set_yscale("log")

    fig.polish(legend_position="lower right")


def graph_rel_star_pressure_mass():

    p0 = 938.565 * 0.16

    files = [
        "rel_gamma5-3.csv",
        "rel_gamma4-3.csv",
        "rel_gamma2.54.csv"
    ]

    labels = [ 
        r"$\Gamma = \frac{5}{3}$",
        r"$\Gamma = \frac{4}{3}$",
        r"$\Gamma = 2.54$"
    ]

    colors = [
        "red",
        "olivedrab",
        "blue",
    ]

    fig = putils.graph.PFig( pyplot.figure(), "Pressione e massa solare a confronto", r"Pressione [$MeV fm^{-3}$]", r"Massa [$M_{\odot}$]")


    for (file, label, color) in zip(files, labels, colors):

        a = extract(join("data", file))

        P = np.array( a[2] ) * p0
        m = np.array( a[1] )

        fig.data(P, m, label=label, color= color, linestyle="-")

    axes = pyplot.gca()

    axes.set_xscale("log")
    axes.set_yscale("log")

    fig.polish(legend_position="lower right")




def graph_harmonic_vernel():

    a = extract(join("data", "harmonic_vel-ver.csv"))

    fig = putils.graph.PFig( 
        pyplot.figure(),
        "Oscillatore armonico", 
        "x", "y"
    )

    t = np.arange(len(a[0]))

    colors = [
        "red",
        "olivedrab",
        "blue",
    ]


    for dat, color in zip(a, colors):

        fig.data(t, dat, color= color, linestyle="-")

    fig.polish(show= False)



def graph_err_star_radius():

    a = extract( join( "data", "rm_error_star.csv"))[:-1]

    fig = putils.graph.PFig( 
        pyplot.figure(),
        "Errore sull raggio", 
        "h [Km]", "Errore %"
    )

    a = np.abs(np.array(a))[:, :-1]

    t = a[4]

    axes = pyplot.gca()

    axes.set_xscale("log")
    axes.set_yscale("log")
    axes.invert_xaxis()

    fig.data(t, a[0], label= "Eulero", linestyle="-")
    fig.data(t, a[2], label= "Runge-Kutta", linestyle="-")


    fig.polish(show= False)

    

def graph_err_star_mass():

    a = extract( join( "data", "rm_error_star.csv"))[:-1]

    fig = putils.graph.PFig( 
        pyplot.figure(),
        "Errore sulla massa", 
        "h [Km]", "Errore %"
    )

    a = np.abs(np.array(a))[:, :-1]

    t = a[4]

    axes = pyplot.gca()

    axes.set_xscale("log")
    axes.set_yscale("log")
    axes.invert_xaxis()

    fig.data(t, a[1], label= "Eulero", linestyle="-")
    fig.data(t, a[3], label= "Runge-Kutta", linestyle="-")


    fig.polish(show= False)