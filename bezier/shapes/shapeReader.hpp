

#include <iostream>
#include <fstream>
#include <string>


typedef struct Model
{
	int vertices;
	int positions;
	int texels;
	int normals;
	int faces;
}



Model;
class Shape{
public:
	Shape(std::string path);
	Shape();
	~Shape();

	float positions[8][3];
	float texels[14][2];
	float normals[5][3];
	int faces[12][9];

	std::string fp;
	Model model;

	void readFromObj();
	void extractOBJdata();
	
	void read();

	void writeH(std::string fp, std::string name);
	void writeCvertices(std::string fp, std::string name);

};

Shape::Shape(std::string path)
{
	Shape::fp = path;
}
Shape::Shape()
{
}
Shape::~Shape()
{
}

void Shape::readFromObj()
{
	 Model objmodel = {0};
	
	// 3
	// Open OBJ file
	std::ifstream inOBJ;
	inOBJ.open(Shape::fp);
	if(!inOBJ.good())
	{
		std::cout << "ERROR OPENING OBJ FILE" << std::endl;
		exit(1);
	}
	
	// 4
	// Read OBJ file
	while(!inOBJ.eof())
	{
		// 5
		std::string line;
		std::getline(inOBJ, line);
		std::string type = line.substr(0,2);
		
		// 6
		if(type.compare("v ") == 0)
			objmodel.positions++;
		else if(type.compare("vt") == 0)
			objmodel.texels++;
		else if(type.compare("vn") == 0)
			objmodel.normals++;
		else if(type.compare("f ") == 0)
			objmodel.faces++;
	}
	
	// 7
	objmodel.vertices = objmodel.faces*3;
	
	// 8
	// Close OBJ file
	inOBJ.close();
	
	// 9
	Shape::model = objmodel;
}
void Shape::read(){
	/*std::cout << "Model Info" << std::endl;
	std::cout << "Positions: " << Shape::model.positions << std::endl;
	std::cout << "Texels: " << Shape::model.texels << std::endl;
	std::cout << "Normals: " << Shape::model.normals << std::endl;
	std::cout << "Faces: " << Shape::model.faces << std::endl;
	std::cout << "Vertices: " << Shape::model.vertices << std::endl;*/
/*
	float positions[8][3];
	float texels[14][2];
	float normals[5][3];
	int faces[12][9];
*/
	extractOBJdata();

	std::cout << "Model Data" << std::endl;
	std::cout << "P1: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << std::endl;
	std::cout << "T1: " << texels[0][0] << "u " << texels[0][1] << "v " << std::endl;
	std::cout << "N1: " << normals[0][0] << "x " << normals[0][1] << "y " << normals[0][2] << "z" << std::endl;
	std::cout << "F1v1: " << faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << std::endl;

}




void Shape::extractOBJdata()
{
	// Counters
	int p = 0;
	int t = 0;
	int n = 0;
	int f = 0;
	
	// Open OBJ file
	std::ifstream inOBJ;
	inOBJ.open(Shape::fp);
	if(!inOBJ.good()){
		std::cout << "ERROR OPENING OBJ FILE" << std::endl;
		exit(1);
	}
	
	// Read OBJ file
	while(!inOBJ.eof()){
		std::string line;
		getline(inOBJ, line);
		std::string type = line.substr(0,2);
		
		// Positions
		if(type.compare("v ") == 0)
		{
			// 1
			// Copy line for parsing
			char* l = new char[line.size()+1];
			memcpy(l, line.c_str(), line.size()+1);
					
			// 2
			// Extract tokens
			strtok(l, " ");
			for(int i=0; i<3; i++)
				Shape::positions[p][i] = atof(strtok(NULL, " "));
			std::cout<<"p:"<<p<<std::endl;
			// 3
			// Wrap up
			delete[] l;
			p++;
		}
		
		// Texels
		else if(type.compare("vt") == 0)
		{
			// 1
			// Copy line for parsing
			char* l = new char[line.size()+1];
			memcpy(l, line.c_str(), line.size()+1);
					
			// 2
			// Extract tokens
			strtok(l, " ");
			for(int i=0; i<3; i++)
				Shape::texels[t][i] = atof(strtok(NULL, " "));
			std::cout<<"t:"<<t<<std::endl;
			
			// 3
			// Wrap up
			delete[] l;
			t++;
		}
		
		// Normals
		else if(type.compare("vn") == 0)
		{
			// 1
			// Copy line for parsing
			char* l = new char[line.size()+1];
			memcpy(l, line.c_str(), line.size()+1);
					
			// 2
			// Extract tokens
			strtok(l, " ");
			for(int i=0; i<3; i++)
				Shape::normals[n][i] = atof(strtok(NULL, " "));
			std::cout<<"n:"<<n<<std::endl;
			// 3
			// Wrap up
			delete[] l;
			n++;
		}
		
		// Faces
		else if(type.compare("f ") == 0)
		{
			// 1
			// Copy line for parsing
			char* l = new char[line.size()+1];
			memcpy(l, line.c_str(), line.size()+1);
					
			// 2
			// Extract tokens
			strtok(l, " ");
			for(int i=0; i<3; i++)
				Shape::faces[f][i] = atof(strtok(NULL, " "));
			std::cout<<"f:"<<f<<std::endl;
			// 3
			// Wrap up
			delete[] l;
			f++;
		}
	}
	
	// Close OBJ file
	inOBJ.close();
}



void Shape::writeH(std::string fp, std::string name)
{
    // 2
    // Create H file
    std::ofstream outH;
    outH.open(fp);
    if(!outH.good())
    {
        std::cout << "ERROR CREATING H FILE" << std::endl;
        exit(1);
    }
    
    // 3
    // Write to H file
    // Write statistics
	outH << "// Positions: " << model.positions << std::endl;
	outH << "// Texels: " << model.texels << std::endl;
	outH << "// Normals: " << model.normals << std::endl;
	outH << "// Faces: " << model.faces << std::endl;
	outH << "// Vertices: " << model.vertices << std::endl;
	outH << std::endl;
		
	// Write declarations
	outH << "const int " << name << "Vertices = " << model.vertices <<";"<< std::endl;
	outH << "const float " << name << "Positions[" << model.vertices*3 << "];" << std::endl;
	outH << "const float " << name << "Texels[" << model.vertices*2 << "];" << std::endl;
	outH << "const float " << name << "Normals[" << model.vertices*3 << "];" << std::endl;
	outH << std::endl;
    

	outH << "const float " << name << "Positions[" << model.vertices*3 << "] = " << std::endl;
    outH << "{" << std::endl;
    for(int i=0; i<model.faces; i++)
    {
        // 3
        int vA = faces[i][0] - 1;
        int vB = faces[i][3] - 1;
        int vC = faces[i][6] - 1;
        
        // 4
        outH << positions[vA][0] << ", " << positions[vA][1] << ", " << positions[vA][2] << ", " << std::endl;
        outH << positions[vB][0] << ", " << positions[vB][1] << ", " << positions[vB][2] << ", " << std::endl;
        outH << positions[vC][0] << ", " << positions[vC][1] << ", " << positions[vC][2] << ", " << std::endl;
    }
    outH << "};" << std::endl;
    outH << std::endl;


    // 4
    // Close H file
    outH.close();
}



void Shape::writeCvertices(std::string fp, std::string name)
{
    // Create C file
    std::ofstream outC;
    outC.open(fp);
    if(!outC.good())
    {
        std::cout << "ERROR CREATING C FILE" << std::endl;
        exit(1);
    }
    
    // Write to C file
    outC << "// This is a .cpp file for the model: " << name << std::endl;
    outC << std::endl;
    
    // Header
    outC << "#include " << "\"" << name << ".hpp" << "\"" << std::endl;
    outC << std::endl;
    
    // Vertices
    outC << "const int " <<"cube::"<< name << "Vertices = " << model.vertices << ";" << std::endl;
    outC << std::endl;
    




    // Close C file
    outC.close();
}

/*
void Shape::writeCpositions(string fp, string name, Model model, int faces[][9], float positions[][3])
{    
    // 2
    // Append C file
    ofstream outC;
    outC.open(fp, ios::app);
    
    // Positions
    outC << "const float " << name << "Positions[" << model.vertices*3 << "] = " << endl;
    outC << "{" << endl;
    for(int i=0; i<model.faces; i++)
    {
        // 3
        int vA = faces[i][0] - 1;
        int vB = faces[i][3] - 1;
        int vC = faces[i][6] - 1;
        
        // 4
        outC << positions[vA][0] << ", " << positions[vA][1] << ", " << positions[vA][2] << ", " << endl;
        outC << positions[vB][0] << ", " << positions[vB][1] << ", " << positions[vB][2] << ", " << endl;
        outC << positions[vC][0] << ", " << positions[vC][1] << ", " << positions[vC][2] << ", " << endl;
    }
    outC << "};" << endl;
    outC << endl;
    
    // Close C file
    outC.close();
}*/