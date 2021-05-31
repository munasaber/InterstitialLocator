#ifndef CLUSTER_FINDER_HH
#define CLUSTER_FINDER_HH

#include <iostream>
//The purpose of this code is to grab sets of clusters and determine potential interstital sites from them given a users specifications
//Gets the clusters sizes to be used in the program
std::vector<int> get_interstitial_coordination(casmutils::fs::path& jsonpath);

//Get the upper bounds of the bond length between the central ion and the coordinating ions
std::vector<double> get_bond_length_maximum(casmutils::fs::path& jsonpath);

//Get the lower bounds of the bond length between the central ion and the coordinating ions
std::vector<double> get_bond_length_minimum(casmutils::fs::path& jsonpath);

//Make pairs of clusters and max lengths
std::vector<pair<int, double>> make_pairs_clusters_and_lengths(casmutils::fs::path& jsonpath);

//necessary for inputting the filtered_sites
bool isDivisibleby4(int value);


//parse site_filter tag from json
std::vector<casmutils::xtal::Site> get_filtered_sites(casmutils::fs::path& jsonpath);


//make filter function for sites that user wants to leave out of the orbit maker function
std::function<bool(const casmutils::xtal::Site)> make_site_filter_func(std::vector<casmutils::xtal::Site> sites_to_be_excluded);

//Make orbits for the relevant cluster sizes
std::vector<casmutils::cluster::Orbit> make_orbits(casmutils::fs::path& jsonpath, casmutils::fs::path& structurepath, double tol);


//get distances between two vectors
double distances_between_vectors(Eigen::Vector3d vector1, Eigen::Vector3d vector2);

//Determine whether there is an atom at the center of the cluster through geometric average (or potentially a smarter method)
bool center_is_empty(casmutils::xtal::Structure structure, casmutils::cluster::Cluster individual_cluster, double tol);
//gets the positions of each sites in the cluster and determines if every distance from the middle of the cluster site is less than the user_determined_cutoff
bool is_cluster_within_length_specification(casmutils::cluster::Cluster individual_cluster, double individual_user_determined_maximum, double individual_user_determined_minimum);

#endif
