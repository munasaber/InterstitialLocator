//The purpose of this code is to grab sets of clusters and determine potential interstital sites from them given a users specifications


//Gets the clusters sizes to be used in the program
std::vector<int> get_interstitial_coordination(casmutils::fs::path& jsonpath)
{
	std::ifstream ifs(jsonpath);
	json j = json::parse(ifs);
	return j.at("interstitial_coordination");
}

//Get the upper bounds of the bond length between the central ion and the coordinating ions
std::vector<double> get_bond_length_maximum(casmutils::fs::path& jsonpath)
{
	std::ifstream ifs(jsonpath);
	json j = json::parse(ifs);
	return j.at("bond_length_maximum");
}

//Get the lower bounds of the bond length between the central ion and the coordinating ions
std::vector<double> get_bond_length_minimum(casmutils::fs::path& jsonpath)
{
	std::ifstream ifs(jsonpath);
	json j = json::parse(ifs);
	return j.at("bond_length_minimum");
}

//Make pairs of clusters and max lengths
std::vector<pair<int, double>> make_pairs_clusters_and_lengths(casmutils::fs::path& jsonpath)
{
	std::vector<pair<int, double>> total_pairs;
	std::vector<int> cluster_size =get_interstitial_coordination(jsonpath);
	std::vector<double> lengths=get_bond_length_maximum(jsonpath);
	for (int i=0; i<cluster_size.size(); i++)
	{
		pair<int, double> individual_pair;
		individual_pair.first=cluster_size[i];
		individual_pair.second=lengths[i];
		total_pairs.emplace_back(individual_pair);
	}
	return total_pairs;
}


//Make orbits for the relevant cluster sizes
std::vector<casmutils::cluster::Orbit> make_orbits(casmutils::fs::path& jsonpath, casmutils::fs::path& structurepath)
{
	
	//Either need a way to skip cluster sizes that differ from what the user chooses or need to choose bond distances of 0	
	//std::vector<double> lengths_vector;
	//std::vector<int> cluster_sizes=get_interstitial_coordination(jsonpath);V
	std::vector<pair<int, double>> cluster_pairs=make_pairs_clusters_and_lengths(jsonpath);
	for (int i=0; i< std::max_element(cluster_pairs.first); i++)
	{
		if std::find_if(cluster_pairs.begin(), cluster_pairs.end(), i)!=cluster_pairs.end()
		{
			lengths_vector.append(cluster_pairs.second);
		}
		else
			lengths_vector.append(0);

	}
	
	//This function needs a lot of work
	//Get max bond distance length from json
	//const std::vector<double> bond_length_maximum=get_length_maximum(jsonpath);
	
	
	//get structure pointer from structure path
	casmutils::xtal::Structure structure= casmutils::xtal::Structure::from_poscar(structurepath);
         	
	//get left out clusters from user input
	const std::vector<casmutils::xtal::Site> filtered_sites(get_filtered_sites(jsonpath));
	std::vector<casmutils::cluster::Orbit> total_orbits= casmutils::cluster::make_periodic_orbits(lengths_vector, structure, make_site_filter_func(filtered_sites));
	return total_orbits;
};


//Grab specific clusters based on size
bool is_cluster_within_size_specification(casmutils::cluster::Cluster inidividual_cluster, std::vector<int> user_determined_size)
{
	
	
}

bool is_cluster_within_length_specification(casmutils::cluster::Cluster inidividual_cluster, std::vector<double> user_determined_cutoff)
{

}

//Determine whether there is an atom at the center of the cluster through geometric average (or potentially a smarter method)
bool center_is_empty(casmutils::xtal::Structure structure, casmutils::cluster::Cluster individual_cluster)
{
	return 0;
}

//
int main()
{

	if (cluster_size.size()!=(max_lengths.size() ||  min_lengths.size()))
		throw "There are an unequal number of entries for the coordination inputs and the bond lengths are unequal";

}



