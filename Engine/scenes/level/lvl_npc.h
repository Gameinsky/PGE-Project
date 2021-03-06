#ifndef LVL_NPC_H
#define LVL_NPC_H

#include "lvl_base_object.h"
#include <data_configs/obj_npc.h>
#include <PGE_File_Formats/file_formats.h>
#include <common_features/npc_animator.h>
#include <common_features/event_queue.h>
#include <common_features/pointf.h>
#include "npc_detectors/lvl_base_detector.h"
#include "npc_detectors/lvl_dtc_player_pos.h"
#include "npc_detectors/lvl_dtc_contact.h"
#include "npc_detectors/lvl_dtc_inarea.h"

#include <luabind/luabind.hpp>
#include <lua_inclues/lua.hpp>

#include <QHash>

class LVL_Player;
class LVL_Npc : public PGE_Phys_Object
{
public:
    LVL_Npc(LevelScene *_parent=NULL);
    virtual ~LVL_Npc();
    void init();

    void setScenePointer(LevelScene* _pointer);

    LevelNPC getData();

    int _npc_id;//Current NPC-ID
    LevelNPC data; //Local settings

    //! Default GFX offset
    PGE_PointF offset;

    //! Configurable GFX Offset from lua scripts
    PGE_PointF lua_offset;

    PGE_Size frameSize;
    AdvNpcAnimator animator;

    void setDirection(int dir);
    int  direction();
    int _direction;
    double motionSpeed;
    bool  is_scenery;
    bool  is_activity;
    bool  is_shared_animation;
    bool  keep_position_on_despawn;

    bool animated;
    long animator_ID;

    obj_npc *setup;//Global config
    bool isKilled();
    bool killed;
    enum DamageReason{
        DAMAGE_NOREASON=0,
        DAMAGE_STOMPED,   //on stomping to head
        DAMAGE_BY_KICK,   //caused by contact with throwned NPC's
        DAMAGE_BY_PLAYER_ATTACK, //Caused by attaking by player
        //(for example, by sword, by fists, by teeth sting, by blow claws, by whip, etc.)
        DAMAGE_TAKEN, //is Power up taken
        DAMAGE_LAVABURN, //Does NPC burn in lava
        DAMAGE_PITFALL, //Does NPC fell into the pit
        DAMAGE_CUSTOM_REASON
    };
    void doHarm(int damageReason);
    void harm(int damage=1, int damageReason = DAMAGE_NOREASON);

    void talkWith();

    void kill(int damageReason);//! In-Game destroying of NPC with triggering of specific events
    void unregister();          //! Sielent destroying of NPC without triggering of the events

    int taskToTransform;
    int taskToTransform_t;
    void transformTo(long id, int type=0);
    void transformTo_x(long id);
    LVL_Block* transformedFromBlock;
    int transformedFromBlockID;
    int transformedFromNpcID;

    void update(double tickTime);
    void render(double camX, double camY);
    void setDefaults();
    void Activate();
    void deActivate();

    void processContacts();
    void preCollision();
    void postCollision();
    void collisionHitBlockTop(std::vector<PGE_Phys_Object*> &blocksHit);
    bool preCollisionCheck(PGE_Phys_Object* body);

    bool forceCollideCenter;//!< collide with invizible blocks at center
    float _heightDelta; //Delta of changing height. Need to protect going through block on character switching
    bool onCliff();
    bool LEGACY_cliffDetected;

    /*****************NPC's and blocks******************/
    bool onGround();
    bool  _onGround;
    QHash<intptr_t, intptr_t > foot_contacts_map;   //!< staying on ground surfaces
    QHash<intptr_t, intptr_t > foot_sl_contacts_map;//!< Slipery surfaces

    typedef QHash<intptr_t, PGE_Phys_Object*> CollisionTable;
    QHash<intptr_t, PGE_Phys_Object*> contacted_blocks;
    QHash<intptr_t, PGE_Phys_Object*> contacted_bgos;
    QHash<intptr_t, PGE_Phys_Object*> contacted_npc;
    QHash<intptr_t, PGE_Phys_Object*> contacted_players;
    inline void l_pushBlk(PGE_Phys_Object*ob) { contacted_blocks[intptr_t(ob)] = ob; }
    inline void l_pushBgo(PGE_Phys_Object*ob) { contacted_bgos[intptr_t(ob)] = ob; }
    inline void l_pushNpc(PGE_Phys_Object*ob) { contacted_npc[intptr_t(ob)] = ob; }
    inline void l_pushPlr(PGE_Phys_Object*ob) { contacted_players[intptr_t(ob)] = ob; }

    bool  m_disableBlockCollision;
    bool  disableNpcCollision;
    bool  enablePlayerCollision;
    bool _stucked;

    bool    bumpDown;
    bool    bumpUp;
    /***************************************************/
    /*******************Environmept*********************/
    //QHash<int, obj_player_physics > physics;
    QHash<intptr_t, intptr_t> environments_map;
    //obj_player_physics physics_cur;
    int     environment;
    int     last_environment;
    /*******************Environmept*********************/

    bool reSpawnable;
    bool isActivated;
    bool deActivatable;
    bool wasDeactivated;
    bool offSectionDeactivate;
    int  activationTimeout;
    int  m_spawnedGeneratorType;
    int  m_spawnedGeneratorDirection;

    /********************Detectors**********************/
    //!< dummy detectors made directly from a base class, for a some tests
    QList<BasicDetector >           detectors_dummy;
    //! Player position detectors (should have alone copy!)
    PlayerPosDetector               detector_player_pos;
    //! Detects position and direction of nearest player
    PlayerPosDetector * lua_installPlayerPosDetector();
    //! Is player touches selected relative area;
    QList<InAreaDetector >          detectors_inarea;
    //! Detects is player(s) are enters into specific area relative to NPC's center
    InAreaDetector *    lua_installInAreaDetector(float left, float top, float right, float bottom, luabind::adl::object filters);
    //! Entire list of all detectors
    QList<ContactDetector >         detectors_contact;
    //! Detects contacted elements
    ContactDetector *   lua_installContactDetector();

    //! Entire list of all detectors
    QVector<BasicDetector* >        detectors;

    /***************************************************/

    /*****Warp*Sprite*****/
    enum WarpingSide{
        WARP_TOP=1,
        WARP_LEFT=2,
        WARP_BOTTOM=3,
        WARP_RIGHT=4,
    };
    ///
    /// \brief setSpriteWarp Changes warping state of a sprite
    /// \param depth
    /// \param direction
    ///
    void setSpriteWarp(float depth, WarpingSide _direction=WARP_BOTTOM, bool resizedBody=false);
    void resetSpriteWarp();
    bool    isWarping;
    int     warpDirectO;
    bool    warpResizedBody;
    float   warpSpriteOffset;
    float   warpFrameW;
    float   warpFrameH;
    /*********************/

    /***************************************************/
    void setWarpSpawn(WarpingSide side=WARP_TOP);
    bool warpSpawing;
    EventQueue<LVL_Npc> event_queue;
    /***************************************************/

    /***********************Generator*******************/
    bool  m_isGenerator;
    float generatorTimeLeft;
    int   generatorType;
    int   generatorDirection;
    void  updateGenerator(float tickTime);
    /***************************************************/

    /*******************Throwned*by*********************/
    void        resetThrowned();
    void        setThrownedByNpc(long npcID,    LVL_Npc *npcObj);
    void        setThrownedByPlayer(long playerID, LVL_Player *npcObj);
    long        thrownedByNpc();
    LVL_Npc    *thrownedByNpcObj();
    long        thrownedByPlayer();
    LVL_Player *thrownedByPlayerObj();
    long        throwned_by_npc;
    LVL_Npc    *throwned_by_npc_obj;
    long        throwned_by_player;
    LVL_Player *throwned_by_player_obj;
    /***************************************************/

    /*******************Buddies********************/
    //Allows communication between neighour NPC's of same type.
    void             buildBuddieGroup();
    void             updateBuddies(float tickTime);
    void             buildLeaf(QList<LVL_Npc*> &needtochec, QList<LVL_Npc*> *&list, LVL_Npc *leader);
    QList<LVL_Npc*> *buddies_list;//Destroys when was killed last NPC in this group
    bool             buddies_updated;
    LVL_Npc*         buddies_leader;
    /**********************************************/

    class KillEvent
    {
        public:
            KillEvent();
            KillEvent(const KillEvent &ke);
            bool cancel;
            int  reason_code;
            enum killedBy {
                self=0,
                player,
                otherNPC
            };
            int         killed_by;
            LVL_Player* killer_p;
            LVL_Npc*    killer_n;
    };

    class HarmEvent
    {
        public:
            HarmEvent();
            HarmEvent(const HarmEvent &he);
            bool cancel;
            int  damage;
            int  reason_code;
            enum killedBy {
                self=0,
                player,
                otherNPC
            };
            int         killed_by;
            LVL_Player* killer_p;
            LVL_Npc*    killer_n;
    };
    //Additional lua enums

    /********************Lua Stuff*******************
                        .-""""-
                       F   .-'
                      F   J
                     I    I
                      L   `.
                       L    `-._,
                        `-.__.-'
     ***********************************************/
    //Additional lua events
    virtual void lua_onActivated() {}
    virtual void lua_onLoop(float) {}
    virtual void lua_onInit() {}
    virtual void lua_onKill(KillEvent*) {}
    virtual void lua_onHarm(HarmEvent*) {}
    virtual void lua_onTransform(long) {}

    //Additional lua functions
    void lua_setSequenceLeft(luabind::object frames);
    void lua_setSequenceRight(luabind::object frames);
    void lua_setSequence(luabind::object frames);
    void lua_setOnceAnimation(bool en);
    bool lua_animationIsFinished();
    int  lua_frameDelay();
    void lua_setFrameDelay(int ms);
    int lua_activate_neighbours();
    LVL_Npc *lua_spawnNPC(int npcID, int sp_type, int sp_dir, bool reSpawnable=false);

    inline void lua_setGfxOffsetX(double x) { lua_offset.setX(x); }
    inline void lua_setGfxOffsetY(double y) { lua_offset.setY(y); }
    inline void lua_setGfxOffset(double x, double y) { lua_offset.setPoint(x, y); }

    inline bool not_movable() { return data.nomove; }
    inline void setNot_movable(bool n) { data.nomove=n; }
    inline long contents() { return data.contents; }
    inline void setContents(long c) { data.contents=c; }
    inline long special1() { return data.special_data; }
    inline void setSpecial1(long s) { data.special_data=s; }
    inline long special2() { return data.special_data2; }
    inline void setSpecial2(long s) { data.special_data2=s; }
    inline bool isBoss() { return data.is_boss; }
    inline int  getID() { return _npc_id; }
    inline long getHealth() { return health; }
    inline void setHealth(int _health) { health=_health; }
    inline bool getCollideWithBlocks() { return !m_disableBlockCollision; }
    inline void setCollideWithBlocks(bool blkcol) { m_disableBlockCollision=!blkcol; }

    inline bool getKillByFire() { return setup->setup.kill_by_fireball; }
    inline bool getKillByIce() { return setup->setup.freeze_by_iceball; }
    inline bool getKillByHammer() { return setup->setup.kill_hammer; }
    inline bool getKillByForcejump() { return setup->setup.kill_by_spinjump; }
    inline bool getKillByStatue() { return setup->setup.kill_by_statue; }
    inline bool getKillByVehicle() { return setup->setup.kill_by_mounted_item; }
    bool isLuaNPC;
    /********************Lua Stuff******************/

    int health;

    /**Layers***/
    void show();
    void hide();

    bool isInited();
private:
    bool m_isInited;

};

#endif // LVL_NPC_H
