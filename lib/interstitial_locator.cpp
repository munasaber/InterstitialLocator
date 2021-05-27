#include <iostream>
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

//necessary for inputting the filtered_sites
bool isDivisibleby4(int value){
   if(value % 4 == 0)
      {
            return true;
      }
    return false;
}


//parse site_filter tag from json
std::vector<casmutils::xtal::Site> get_filtered_sites(casmutils::fs::path& jsonpath)
{
	std::ifstream ifs(jsonpath);
	json j =json::parse(ifs);
	std::vector<std::string> vector_of_sites=j.at("site_filter");
	Eigen::Vector3d my_eigen;
	std::string occupant_type;
	std::vector<casmutils::xtal::Site> site_list;
	for (int i=0; i<vector_of_sites.size(); i=i+4)
	{
		Eigen::Vector3d my_eigen(std::stod(vector_of_sites[i]), std::stod(vector_of_sites[i+1]), std::stod(vector_of_sites[i+2]));
		site_list.emplace_back(casmutils::xtal::Site(my_eigen, vector_of_sites[i+3]));
	}
	if(!isDivisibleby4(vector_of_sites.size()))
	{
		throw "Division by zero condition!";
	}
	return site_list;
}


//make filter function for sites that user wants to leave out of the orbit maker function
std::function<bool(const casmutils::xtal::Site)> make_site_filter_func(std::vector<casmutils::xtal::Site> sites_to_be_excluded)
{
	std::function<bool(const casmutils::xtal::Site)> my_func=[&](casmutils::xtal::Site site)
	{
		casmutils::xtal::SiteEquals_f site_comparator(1e-6);
		for (const auto& x: sites_to_be_excluded)
		{
			if (site_comparator(x, site))
			{
				return false;
			}
		}
	return true;
	};
return my_func;
}

//Make orbits for the relevant cluster sizes
std::vector<casmutils::cluster::Orbit> make_orbits(casmutils::fs::path& jsonpath, casmutils::fs::path& structurepath, double tol)
{
	
	//Either need a way to skip cluster sizes that differ from what the user chooses or need to choose bond distances of 0	
	std::vector<double> lengths_vector;
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
	
	//get structure pointer from structure path
	casmutils::xtal::Structure structure= casmutils::xtal::Structure::from_poscar(structurepath);
         	
	//get left out clusters from user input
	const std::vector<casmutils::xtal::Site> filtered_sites(get_filtered_sites(jsonpath));
	std::vector<casmutils::cluster::Orbit> total_orbits= casmutils::cluster::make_periodic_orbits(lengths_vector, structure, make_site_filter_func(filtered_sites));
	std::vector<casmutils::cluster::Orbit> filtered_orbits;
	for (const auto& orbit: total_orbits)
	{
		if center_is_empty(structure, orbit.prototpye(), tol)
		{
			if is_cluster_within_length_specification(orbit.prototype(), get_bond_length_maximum(jsonpath)[orbit.prototype().size()], get_bond_length_minimum[orbit.prototype().size()]
			{
				filtered_orbits.emplace_back(orbit)
			}
		}
	}
	return filtered_orbits;
};


//Grab specific clusters based on size
//bool is_cluster_within_size_specification(casmutils::cluster::Cluster inidividual_cluster, int individual_user_determined_size)
//{
//	if (individual_cluster.size()!=individual_user_determined_size)
//		return False;
//	return True;
//	//Need to revisit for cases that the user determined size is 0 or the individual_cluster size is 0
//	
//}

//get distances between two vectors
double distances_between_vectors(Eigen::Vector3d vector1, Eigen::Vector3d vector2)
{
	double distance=sqrt((vector2[0]-vector1[0])^2+(vector2[1]-vector1[1])^2+(vector2[2]-vector[1])^2);
	if (distance<0)
		throw "The distance between two vectors should not be negative";
	return distance;
}

//Determine whether there is an atom at the center of the cluster through geometric average (or potentially a smarter method)
bool center_is_empty(casmutils::xtal::Structure structure, casmutils::cluster::Cluster individual_cluster, double tol)
{
	//Vector compare between geoemetric center of mass and all site coordiantes in the lattice
	CoordinateEquals_f comparator(tol);
	for (const auto& vector : individual_cluster.m_sites.cart())
	{
		if comparator(individual_cluster.geometric_center_of_mass(), vector)
			return True;
	}
	return False;
}

//gets the positions of each sites in the cluster and determines if every distance from the middle of the cluster site is less than the user_determined_cutoff
bool is_cluster_within_length_specification(casmutils::cluster::Cluster individual_cluster, double individual_user_determined_maximum, double individual_user_determined_minimum)
{
	//need to do this for each cutoff
	std::vector<Eigen::Vector3d> vectors_in_cluster= individual_cluster.m_sites.cart();
	Eigen::Vector3d center_of_mass=individual_cluster.geometric_center_of_mass();
	for (const auto& vector : vectors_in_cluster)
	{
		double distance=distances_between_vectors(vector, center_of_mass);
		if distance> individual_user_determined_maximum || distance < individual_user_determined_minimum
			return False;
	}
	//Would I need to throw an exception if the size of the cluster is zero (or make it false)?
	return True;	
}




//
int main()
{
        make_orbits(casmutils::fs::path& jsonpath, casmutils::fs::path& structurepath, double tol)
	if (cluster_size.size()!=(max_lengths.size() ||  min_lengths.size()))
		throw "There are an unequal number of entries for the coordination inputs and the bond lengths";
	return 0;
}



