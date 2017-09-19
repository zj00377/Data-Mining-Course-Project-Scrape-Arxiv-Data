#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int main(int argc, char* argv[])
{
  std::vector<std::string> datafiles;
  std::map<std::string,int> authormap;
  std::map<int,int> edgelist;
  std::vector<int> authorgroup;
  int amap_idx = 0;
  std::string outstr = "";

  int num_years = 0;
  if (argc > 2)
  {
    num_years = atoi(argv[2]);
    std::cout << "number of previous years: " << num_years << std::endl;
  }
  else
  {
    std::cout << "ERROR: not enough parameters" << std::endl;
    std::cout << "Command: $./parse.o <files list> <number of years>" << std::endl;
    std::cout << std::endl;
    std::cout << "<files list> = text file containing list of files to parse. Each line is path to one file. Each file is 1 year of data." << std::endl;
    std::cout << "<number of years> = number of years to parse (equal to number of files). NOTE: some files could be missing" << std::endl;
    return 0;
  }

  std::string line;
  std::ifstream infile;
  std::ofstream outfile;

  /* List of data files to parse */
  infile.open(argv[1]);
  if (infile.is_open())
  {
    std::cout << "Files to parse:" << std::endl;
    while ( !infile.eof() )
    {
      std::getline (infile,line);

      if (line.length() > 0)
      {
        datafiles.push_back(line);
        std::cout << line << std::endl;
      }
    }
    infile.close();
  }
  else
  {
    std::cout << "ERROR: cannot open files list" << std::endl;
    return 0;
  }

  //outfile.open ("edgelist_" + std::to_string(num_years) + ".txt", std::ofstream::out | std::ofstream::app);
  outfile.open ("edgelist_" + std::to_string(num_years) + ".txt", std::ofstream::out);
  if (!outfile.is_open())
  {
    std::cout << "Unable to open file edgelist.txt for writing" << std::endl;
    
    return 0;
  }

  int max_scrape = num_years;
  if (num_years > datafiles.size())
  {
    max_scrape = datafiles.size();
  }

  //std::cout << "max map size: " << edgelist.max_size() << std::endl;

  std::cout << std::endl << "Processing " << max_scrape << " years of data" << std::endl;
  for(int i = 0; i < max_scrape; i++)
  {
    std::cout << "processing: "<< datafiles[i] << std::endl;

    infile.open(datafiles[i]);
    if (infile.is_open())
    {
      int linecount = 0;
      int stroffset = 0;
      //while ( !infile.eof() && linecount < 17 )
      while ( !infile.eof() )
      {
        std::getline (infile,line);

        // DEBUG: output current line read
        //std::cout << line << '\n';

        // position of "$[" in str, which indicates start of author
        // names list
        std::size_t pos = line.find("$[");

        if (pos > line.length() )
        {
          pos = line.find("$\"[");
          if (pos > line.length() )
          {
            std::cout << "ERROR: author list not found $[...] at line: " << linecount << std::endl;
            continue;
          }
          else
          {
            stroffset = 3;
          }
        }
        else
        {
          stroffset = 2;
        }
        
        // get the substring containing author names
        std::string authors = line.substr (pos+stroffset);

        // DEBUG: output authors string
        //std::cout << authors << std::endl;

        // parse each author in string
        std::string author = "";
        authorgroup.clear();

        while (1)
        {
          pos = authors.find(",");

          if (pos > authors.length())
          {
            pos = authors.find("]");

            if (pos > authors.length())
            {
              break;
            }
            else
            {
              stroffset = 0;
            }
          }
          else
          {
            stroffset = 2;
          }

          author = authors.substr (0, pos);

          // DEBUG: output parsed author name
          //std::cout << author << std::endl;

          // check if key is present
          if (authormap.find(author) == authormap.end())
          {
            // put into hash map
            authormap[author] = amap_idx;

            // add to current group of authors
            authorgroup.push_back(amap_idx);

            amap_idx++;
          }
          else
          {
            // add to current group of authors
            authorgroup.push_back(authormap[author]);
          }

          // update substring to discard already parsed substring
          if (stroffset > 0)
          {
            authors = authors.substr (pos+stroffset);
          }
          else
          {
            break;
          }
        }

        // DEBUG: print out current parsed author group
        //for (int agidx = 0; agidx < authorgroup.size(); agidx++)
        //{
        //  std::cout << authorgroup[agidx] << " ";
        //}
        //std::cout << std::endl;

        // Update vertex list
        if (authorgroup.size() > 1)
        {
          bool empty_edge_list = true;
          outstr.clear();

          for (int ag_i = 0; ag_i < authorgroup.size() - 1; ag_i++)
          {
            for (int ag_j = (ag_i+1); ag_j < authorgroup.size(); ag_j++)
            {
              // check if vertex is already in edge list -- bidirectional so only need to check key for one of the vertex
              if (edgelist.find(authorgroup[ag_i]) == edgelist.end())
              {
                // map both direction for non-directional graph
                edgelist[authorgroup[ag_i]] = authorgroup[ag_j];
                edgelist[authorgroup[ag_j]] = authorgroup[ag_i];

                outstr.append("("+ std::to_string(authorgroup[ag_i]) + " " + std::to_string(authorgroup[ag_j]) + ")" + "#");
                
                // there is a new edge
                empty_edge_list = false;
              }
              else
              {
                if (edgelist[authorgroup[ag_i]] != authorgroup[ag_j])
                {
                  // map both direction for non-directional graph
                  edgelist[authorgroup[ag_i]] = authorgroup[ag_j];
                  edgelist[authorgroup[ag_j]] = authorgroup[ag_i];

                  outstr.append("("+ std::to_string(authorgroup[ag_i]) + " " + std::to_string(authorgroup[ag_j]) + ")" + "#");

                  // there is a new edge
                  empty_edge_list = false;
                }
              }
            }
          }

          if (!empty_edge_list)
          {
            outfile << outstr << std::endl;
          }
        }
        linecount++;
      }
      infile.close();
      outfile.close();

      // DEBUG: print out mapped vertex list
      //for (std::map<int,int>::iterator vidx = edgelist.begin(); vidx != edgelist.end(); ++vidx)
      //{
      //  std::cout << vidx->first << std::endl;
      //}

      //outfile.open ("vertexlist_" + std::to_string(num_years) + ".txt", std::ofstream::out | std::ofstream::app);=
      outfile.open ("vertexlist_" + std::to_string(num_years) + ".txt", std::ofstream::out);
      if (outfile.is_open())
      {
        // print out author -> index map
        for (std::map<std::string,int>::iterator mapidx = authormap.begin(); mapidx != authormap.end(); ++mapidx)
        {
          outfile << "Author:" << mapidx->first << " Key:" << mapidx->second << '\n';
        }
        outfile.close();
      }
      else
      {
        std::cout << "Unable to open file vertexlist_" << std::to_string(num_years) << ".txt" << std::endl;
      }
    }
    else
    {
      std::cout << "Unable to open file " << datafiles[i] << std::endl;
    }
  } 
}

