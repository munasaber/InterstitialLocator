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

//Construct maximum Cluster; The cluster dimension is the highest intersttial_coordination number



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


}



