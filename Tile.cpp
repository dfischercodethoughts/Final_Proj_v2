//
// Created by david on 4/3/2019.
//

#include "Tile.h"
#include "Texture.h"
#include <vector>

int Tile::num_tiles = 0;

void Tile::init_output() {
    switch (terrain) {
        case (Tile_Terrain::WATER) : {
            output.increment_food();
            break;
        }
        case (Tile_Terrain::MOUNTAIN) : {
            output.increment_production();
            break;
        }
        case (Tile_Terrain::GRASSLAND) : {
            output.increment_food();
            break;
        }
        case (Tile_Terrain::HILL) : {
            output.increment_production();
            break;
        }
        default:
            break;
    }
}

void Tile::clear_resource() {
    switch ( resource) {
        case ( Tile_Resource::STONE) : {
            output.decrement_production();
            resource = Tile_Resource::DEFAULT;
            break;
        }
        case ( Tile_Resource::GOLD) : {
            output.decrement_gold();
            resource = Tile_Resource::DEFAULT;
            break;
        }case ( Tile_Resource::SILVER) : {
            output.decrement_gold();
            resource = Tile_Resource::DEFAULT;
            break;
        }
        case ( Tile_Resource::WOODS) : {
            output.decrement_production();
            resource = Tile_Resource::DEFAULT;
            break;
        }
        case ( Tile_Resource::WHEAT) : {
            output.decrement_food();
            resource = Tile_Resource::DEFAULT;
            break;
        }
        case ( Tile_Resource::GAZELLE) : {
            output.decrement_food();
            resource = Tile_Resource::DEFAULT;
            break;
        }
        case ( Tile_Resource::IRON) : {
            output.decrement_production();
            resource = Tile_Resource::DEFAULT;
            break;
        }
        default:
            break;
    }
}

Tile::Tile():
Piece(Piece::TILE), building(Building())
{
    num_tiles++;
    init(Tile_Terrain::DEFAULT,Tile_Resource::DEFAULT,nullptr,false);
}

Tile::Tile(Tile *cp):
Piece(cp->get_center(),cp->get_height(),cp->get_width(),cp->get_fill(),cp->get_text_color(),Piece::TILE)
{
    num_tiles++;
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),cp->is_visible(),cp->get_id());
}

Tile::Tile(const Tile *cp):
        Piece(cp->get_center(),cp->get_height(),cp->get_width(),cp->get_fill(),cp->get_text_color(),Piece::TILE)
{
    num_tiles++;
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),cp->is_visible(),cp->get_id());
}

Tile::Tile(const Tile & cp):
Piece(cp.get_center(),cp.get_height(),cp.get_width(),cp.get_fill(),cp.get_text_color(),Piece::TILE)
{
    num_tiles++;
    init(cp.get_terrain(),cp.get_resource(),cp.get_const_unit(),cp.is_visible(),cp.get_id());
}

Tile::Tile(std::unique_ptr<Tile> cp):
Piece(Piece::TILE), building(Building())
{
    num_tiles++;
    init(cp->get_terrain(),cp->get_resource(),cp->get_const_unit(),cp->is_visible(),cp->get_id());
}

Tile::Tile(std::string ter, std::string res):
Piece(Piece::TILE)
{
    num_tiles++;
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),nullptr,false);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res):
Piece(Piece::TILE)
{
    num_tiles++;
    init(ter,res,nullptr,false);
}

Tile::Tile(std::string ter, std::string res, Unit & u):
Piece(u.get_center(),u.get_height(),u.get_width(),u.get_fill(),u.get_text_color(),Piece::TILE), building(Building()){
    num_tiles++;
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),&u,false);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res, Unit & u):
Piece(u.get_center(),u.get_height(),u.get_width(),u.get_fill(),u.get_text_color(),Piece::TILE), building(Building()) {
    num_tiles++;
    init(ter,res,unit,false);
}

Tile::Tile(Tile_Terrain::names nm):
Piece(Piece::TILE), building(Building())
{
    num_tiles++;
    init(nm,Tile_Resource::DEFAULT,nullptr,false);
}

Tile::Tile(std::string ter, std::string res, std::shared_ptr<Unit> & u):
Piece(u->get_center(),u->get_height(),u->get_width(),u->get_fill(),u->get_text_color(),Piece::TILE), building(Building())
{
    num_tiles++;
    init(Tile_Terrain::string_to_terrain(ter),Tile_Resource::string_to_resource(res),&*u,false);
}

Tile::Tile(Tile_Terrain::names ter,Tile_Resource::names res, std::shared_ptr<Unit> & u):
Piece(u->get_center(),u->get_height(),u->get_width(),u->get_fill(),u->get_text_color(),Piece::TILE), building(Building())
{
    num_tiles++;
    init(ter,res,&*u,false);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res):
Piece(cnt,h,w,fill,text,Piece::TILE), building(Building())
{
    num_tiles++;
    init(ter,res,nullptr,false);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res,int i):
        Piece(cnt,h,w,fill,text,Piece::TILE), building(Building())
{
    num_tiles++;
    init(ter,res,nullptr,false,i);
}

Tile::Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res,bool vis):
        Piece(cnt,h,w,fill,text,Piece::TILE), building(Building())
{
    num_tiles++;
    init(ter,res,nullptr,vis);
}

void Tile::init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * u, bool vis) {
    terrain = ter;
    resource = res;
    unit = &*u;
    owner = Civilization_Name::NONE;
    if(vis) {
        this->reveal();
    }
    else {
        this->hide();
    }
    init_output();
    id = get_num_tiles();
    city = nullptr;
}

void Tile::init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * u, bool vis, int i) {
    terrain = ter;
    resource = res;
    unit = &*u;
    owner = Civilization_Name::NONE;
    city = nullptr;
    if(vis) {
        this->reveal();
    }
    else {
        this->hide();
    }
    init_output();
    id = i;
}

int Tile::get_num_tiles() {
    return Tile::num_tiles;
}

void Tile::increment_num_tiles() {
    Tile::num_tiles = Tile::num_tiles+1;
}

void Tile::init_id() {
    Tile::num_tiles = 0;
}

Civilization_Name::Names Tile::get_owner() const {
    return owner;
}

void Tile::set_owner(Civilization_Name::Names nm) {
    owner = nm;
}

bool Tile::has_owner() const {
    return owner!=Civilization_Name::NONE;
}

Building Tile::get_building() const {
    return building;
}

Square Tile::get_base_square() const {
    Square toret(this->get_center(),this->get_fill(),this->get_text_color(),this->get_height(),this->get_width(),this->get_message(),this->is_visible());
    toret.set_x_offset(this->get_x_offset());
    toret.set_y_offset(this->get_y_offset());
    return toret;
}

City * Tile::get_city() {
    return city;
}

void Tile::set_city(City & newc) {
    city = &newc;
}

void Tile::build_city(City & newc) {
    city = &newc;
}

bool Tile::has_city() const {
    return (city!=nullptr);
}

void Tile::remove_city() {
    city = nullptr;
}

void Tile::set_base_square(Square set) {
    this->set_center(set.get_center());
    this->set_y_offset(set.get_y_offset());
    this->set_x_offset(set.get_x_offset());
    this->set_fill(set.get_fill());
    this->set_text_color(set.get_text_color());
    this->set_width(set.get_width());
    this->set_height(set.get_height());
    this->set_message(set.get_message());
    if (set.is_visible()) {
        this->reveal();
    }
    else {
        this->hide();
    }
}

Tile_Terrain::names Tile::get_terrain() const {
    return terrain;
}

Tile_Resource::names Tile::get_resource() const {
    return resource;
}

int Tile::get_id() const {
    return id;
}

void Tile::clear_unit() {

    unit = nullptr;
}

bool Tile::has_unit() const {
    return unit != nullptr;
}

Unit* Tile::get_const_unit() const {
    return &*unit;
}

Unit* Tile::get_unit() {
    return &*unit;
}

void Tile::set_unit(Unit &newu) {
    unit = &newu;
}

void Tile::set_unit(Unit *newu) {
    unit = newu;
}

void Tile::set_background_square(Square set) {
    this->set_center(set.get_center());
    this -> set_x_offset(set.get_x_offset());
    this->set_y_offset(set.get_y_offset());
    this->set_text_color(set.get_text_color());
    this->set_message(set.get_message());
    this->set_fill(set.get_fill());
    if (set.is_visible()) {
        this->reveal();
    }
    else {
        this->hide();
    }
    this->set_height(set.get_height());
    this->set_width(set.get_width());
}

bool Tile::has_building() const {
    return (building.get_name() != Building_Name::NONE);
}

bool Tile::add_building(Building_Name::names bld) {
    bool built = false;

    switch (bld) {
        case (Building_Name::BARRACKS) : {
            clear_resource();
            break;
        }
        case (Building_Name::MINE) : {
            switch (terrain) {
                case (Tile_Terrain::GRASSLAND) : {
                    building = Building(bld);
                    output.increment_production();
                    built = true;
                    break;
                }
                case (Tile_Terrain::HILL) : {
                    building = Building(bld);
                    output.increment_production();
                    built = true;
                    break;
                }
                case ( Tile_Terrain::MOUNTAIN) : {
                    building = Building(bld);
                    output.increment_production();
                    output.increment_gold();
                    built = true;
                    break;
                }
                default : {
                    return false;
                }
            }
            if (resource == Tile_Resource::SILVER || resource == Tile_Resource::GOLD) {
                output.increment_gold();
                output.increment_gold();
            }
            else if (resource == Tile_Resource::STONE) {
                output.increment_production();
                output.increment_production();
            }
            else {
                clear_resource();
            }
            break;
        }
        case (Building_Name::FARM) : {
            switch (terrain) {
                case (Tile_Terrain::GRASSLAND) : {
                    building = Building(bld);
                    output.increment_food();
                    built = true;
                    break;
                }
                case (Tile_Terrain::HILL) : {
                    building = Building(bld);
                    output.increment_food();
                    built = true;
                    break;
                }
                default : {
                    return false;
                }
            }
            if (resource == Tile_Resource::WHEAT) {
                output.increment_food();
                output.increment_food();
            }
            else {
                clear_resource();
            }
            break;
        }
        case (Building_Name::LOGGING_CAMP) : {
            if (resource == Tile_Resource::WOODS) {
                building = Building(bld);
                output.increment_production();
                output.increment_production();
                built = true;
            }
            else {
                return false;
            }

            break;
        }
        case (Building_Name::MARKET) : {
            switch (terrain) {
                case (Tile_Terrain::GRASSLAND) : {
                    building = Building(bld);
                    output.increment_gold();
                    output.increment_gold();
                    built = true;
                    break;
                }
                case (Tile_Terrain::HILL) : {
                    building = Building(bld);
                    output.increment_gold();
                    output.increment_gold();
                    built = true;
                    break;
                }
                default : {
                    return false;
                }
            }
            clear_resource();
            break;
        }
        case (Building_Name::HARBOR) : {
            switch (terrain) {
                case (Tile_Terrain::WATER) : {
                    building = Building(bld);
                    output.increment_food();
                    output.increment_gold();
                    built = true;
                    break;
                }
                default : {
                    return false;
                }
            }
            if (resource == Tile_Resource::FISH) {
                output.increment_food();
                output.increment_food();
            }
            else {
                clear_resource();
            }
            break;
        }
        case (Building_Name::TRADING_POST) : {
            switch (terrain) {
                case (Tile_Terrain::GRASSLAND) : {
                    building = Building(bld);
                    output.increment_gold();
                    built = true;
                    break;
                }
                case (Tile_Terrain::HILL) : {
                    building = Building(bld);
                    output.increment_gold();
                    built = true;
                    break;
                }
                default : {
                    return false;
                }
            }
            break;
        }
        case (Building_Name::WORKSHOP) : {
            switch (terrain) {
                case (Tile_Terrain::GRASSLAND) : {
                    building = Building(bld);
                    output.increment_production();
                    built = true;
                    break;
                }
                case (Tile_Terrain::HILL) : {
                    building = Building(bld);
                    output.increment_production();
                    built = true;
                    break;
                }
                default : {
                    return false;
                }
            }
            if (resource == Tile_Resource::WOODS || resource == Tile_Resource::STONE) {
                output.increment_production();
            }
            else if (resource == Tile_Resource::GOLD || resource == Tile_Resource::SILVER) {
                output.increment_gold();
            }
            else {
                clear_resource();
            }
            break;
        }
        default:
            break;
    }

    return built;
}

Tile_Output Tile::get_output() const {
    if (has_owner() && has_unit() && unit->get_owner() != owner) {
        return *new Tile_Output();
    }

    return output;
}

void Tile::draw() const {
    //draw T: terrain
    //     R: resource
    //     U: unit_type
    if (is_visible()) {

        //draw texture in background map
        TextureManager::GetTexture(Tile_Terrain::terrain_to_string(this->get_terrain()).c_str()).Draw(
                get_center().x - get_width() / 2,
                get_center().y - get_height() / 2,
                get_center().x + get_width() / 2,
                get_center().y + get_height() / 2
        );

        std::vector<std::string> drawItems;
        drawItems.push_back(Tile_Resource::resource_to_string(this->get_resource()));
        if (this->has_unit()) {
            drawItems.push_back(Unit::unit_type_to_string(get_const_unit()->get_unit_type()));
        }

        if (this->has_city())
        {
            drawItems.push_back("city");
        }

        //arrage images according to the number of elements to be drawn
        switch (drawItems.size())
        {
            case 1:
            {
                int centers[][2] = {
                        {get_center().x,get_center().y},
                };
                for (int i=0;i<drawItems.size();++i)
                {

                    Texture &resourceTex = TextureManager::GetTexture(drawItems[i].c_str());
                    float ratio = std::min(get_width()*0.5 / resourceTex.Width(), get_height()*0.5 / resourceTex.Height());
                    auto& center = centers[i];
                    resourceTex.Draw(
                            center[0] - resourceTex.Width()*ratio,
                            center[1] - resourceTex.Height()*ratio,
                            center[0] + resourceTex.Width()*ratio,
                            center[1] + resourceTex.Height()*ratio
                    );
                }
            }
                break;
            case 2:
            {
                int centers[][2] = {
                        { get_center().x - get_width() / 4,get_center().y },
                        { get_center().x + get_width() / 4,get_center().y },
                };
                for (int i = 0; i < drawItems.size(); ++i)
                {

                    Texture &resourceTex = TextureManager::GetTexture(drawItems[i].c_str());
                    float ratio = std::min(get_width()*0.25 / resourceTex.Width(), get_height()*0.5 / resourceTex.Height());
                    auto& center = centers[i];
                    resourceTex.Draw(
                            center[0] - resourceTex.Width()*ratio,
                            center[1] - resourceTex.Height()*ratio,
                            center[0] + resourceTex.Width()*ratio,
                            center[1] + resourceTex.Height()*ratio
                    );
                }
            }
                break;
            case 3:
            {
                int centers[][2] = {
                        { get_center().x - get_width() / 4,get_center().y + get_height() / 4 },
                        { get_center().x + get_width() / 4,get_center().y + get_height() / 4 },
                        { get_center().x,get_center().y - get_height() / 4 },
                };
                for (int i = 0; i < drawItems.size(); ++i)
                {

                    Texture &resourceTex = TextureManager::GetTexture(drawItems[i].c_str());
                    float ratio = std::min(get_width()*0.25 / resourceTex.Width(), get_height()*0.25 / resourceTex.Height());
                    auto& center = centers[i];
                    resourceTex.Draw(
                            center[0] - resourceTex.Width()*ratio,
                            center[1] - resourceTex.Height()*ratio,
                            center[0] + resourceTex.Width()*ratio,
                            center[1] + resourceTex.Height()*ratio
                    );
                }
            }
                break;
            case 4:
            {
                int centers[][2] = {
                        { get_center().x - get_width() / 4,get_center().y + get_height() / 4 },
                        { get_center().x + get_width() / 4,get_center().y + get_height() / 4 },
                        { get_center().x - get_width() / 4,get_center().y - get_height() / 4 },
                        { get_center().x + get_width() / 4,get_center().y - get_height() / 4 },
                };
                for (int i = 0; i < drawItems.size(); ++i)
                {

                    Texture &resourceTex = TextureManager::GetTexture(drawItems[i].c_str());
                    float ratio = std::min(get_width()*0.25 / resourceTex.Width(), get_height()*0.25 / resourceTex.Height());
                    auto& center = centers[i];
                    resourceTex.Draw(
                            center[0] - resourceTex.Width()*ratio,
                            center[1] - resourceTex.Height()*ratio,
                            center[0] + resourceTex.Width()*ratio,
                            center[1] + resourceTex.Height()*ratio
                    );
                }
            }
                break;
        }

    }
        //if not visible print black square
    else {
        Square(get_center(),Colors::BLACK,Colors::WHITE,get_height(),get_width(),"",true).draw();
    }
}

void Tile::draw_on_viewport(Square viewport_base) {
    viewport_base.draw();
    Coordinate tl ={ viewport_base.get_center().x-viewport_base.get_width()/2, viewport_base.get_center().y-viewport_base.get_height()/2};

    std::string line = "";
    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(tl.x+viewport_base.get_width()/28,tl.y+viewport_base.get_height()/3);
    line += "TERRAIN TYPE: " + Tile_Terrain::terrain_to_string(terrain);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(tl.x+viewport_base.get_width()/28,tl.y+viewport_base.get_height()/3+viewport_base.get_height()/12);
    line = "RESOURCE TYPE: " + Tile_Resource::resource_to_string(resource);
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    glColor3f(Colors::BLACK.get_red(),Colors::BLACK.get_green(),Colors::BLACK.get_blue());
    glRasterPos2i(tl.x+viewport_base.get_width()/28,tl.y+viewport_base.get_height()/3 + viewport_base.get_height()/6);
    line = "MOVEMENT COST: "+std::to_string(Tile_Terrain::get_movement_cost(terrain));
    for (char c : line) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,c);
    }

    if (has_building()) {
        glColor3f(Colors::BLACK.get_red(), Colors::BLACK.get_green(), Colors::BLACK.get_blue());
        glRasterPos2i(tl.x + viewport_base.get_width() / 28,
                      tl.y + viewport_base.get_height() / 3 + viewport_base.get_height() / 4);
        line = "BUILDING: " + Building_Name::building_name_to_string(building.get_name());
        for (char c : line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }

    if (has_owner()) {
        glColor3f(Colors::BLACK.get_red(), Colors::BLACK.get_green(), Colors::BLACK.get_blue());
        glRasterPos2i(tl.x + viewport_base.get_width() / 28,
                      tl.y + viewport_base.get_height() / 3 + viewport_base.get_height() / 3);
        line = "OWNER: " + Civilization_Name::civ_name_to_string(get_owner());
        for (char c : line) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
        }
    }
}

std::ostream & operator<<(std::ostream & outs, const Tile & print) {
    std::string line = "TILE\n";
    outs << line;
    outs << print.get_base_square();

    line =Tile_Terrain::terrain_to_string(print.terrain) + "\n" + Tile_Resource::resource_to_string(print.resource) +
            "\n" + Building_Name::building_name_to_string(print.get_building().get_name()) +
            "\n" + std::to_string(print.id);
    outs << line << std::endl;
    return outs;
}

std::istream & operator>>(std::istream & ins, Tile & fill) {
    try {
        //assume "TILE\n" already read
        fill.set_type(Piece::TILE);
        Square base;
        ins >> base;
        fill.set_base_square(base);

        std::string line = "";

        //read terrain
        std::getline(ins, line);
        fill.terrain = Tile_Terrain::string_to_terrain(line);

        //read resource
        std::getline(ins,line);
        fill.resource = Tile_Resource::string_to_resource(line);

        std::getline(ins,line);
        fill.building = Building(Building_Name::string_to_building_name(line));

        std::getline(ins,line);
        fill.id = std::stoi(line);

    }
    catch (std::exception & e) {
        std::cout << e.what() << std::endl;
    }
    return ins;
}

Tile & Tile::operator=(const Tile & rhs) {
    set_center(rhs.get_center());
    set_height(rhs.get_height());
    set_width(rhs.get_width());
    set_text_color(rhs.get_text_color());
    set_fill(rhs.get_fill());
    set_message(rhs.get_message());
    add_building(rhs.get_building().get_name());
    init(rhs.get_terrain(),rhs.get_resource(),rhs.get_const_unit(),rhs.is_visible(),rhs.get_id());
    return *this;
}

bool Tile::operator==(Tile const & rhs) const {
    return ((get_id() == rhs.get_id()) && (terrain == rhs.get_terrain()) &&
            (resource == rhs.get_resource())&& building == rhs.get_building());
}

bool Tile::operator!=(Tile const & rhs) const {
    return (!(*this == rhs));
}

bool Tile::operator<(const Tile & rhs) const {
    return (get_id() < rhs.get_id());
}

Tile::~Tile() {
    id = -1;
    terrain = Tile_Terrain::DEFAULT;
    resource = Tile_Resource::DEFAULT;

    unit = nullptr;
    reveal();
    num_tiles--;
}