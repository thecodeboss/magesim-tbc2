#include <string>
#include <random>

enum RegenRotation : int
{
    ROTATION_FB,
    ROTATION_AMFB,
};

enum Race : int
{
    RACE_BLOOD_ELF,
    RACE_DRAENEI,
    RACE_GNOME,
    RACE_HUMAN,
    RACE_TROLL,
    RACE_UNDEAD
};

enum School : int
{
    SCHOOL_ARCANE,
    SCHOOL_FROST,
    SCHOOL_FIRE,
    SCHOOL_NONE
};

enum Spec : int
{
    SPEC_ARCANE
};

enum MetaGem : int {
    META_NONE = 0,
    META_CHAOTIC_SKYFIRE = 34220,
    META_EMBER_SKYFIRE = 35503,
    META_INSIGHTFUL_EARTHSTORM = 25901,
};

enum Trinket : int
{
    TRINKET_NONE = 0,
    TRINKET_SERPENT_COIL = 30720,
    TRINKET_SILVER_CRESCENT = 29370,
    TRINKET_EYE_OF_MAGTHERIDON = 28789,
    TRINKET_RESTRAINED_ESSENCE = 23046,
    TRINKET_QUAGMIRRANS_EYE = 27683,
    TRINKET_UNSTABLE_CURRENTS = 30626,
    TRINKET_LIGHTNING_CAPACITOR = 28785,
    TRINKET_MQG = 19339,
    TRINKET_BLUE_DRAGON = 19288,
};

enum EventType : int
{
    EVENT_CAST,
    EVENT_SPELL,
    EVENT_MANA_REGEN,
    EVENT_MANA_GAIN,
    EVENT_BUFF_GAIN,
    EVENT_BUFF_EXPIRE,
    EVENT_CD_EXPIRE,
    EVENT_VAMPIRIC_TOUCH,
    EVENT_WAIT
};

enum LogType : int
{
    LOG_NONE,
    LOG_SPELL,
    LOG_MANA,
    LOG_BUFF,
    LOG_DEBUG,
    LOG_WAIT
};

struct LogEntry
{
    LogType type;
    std::string text;
    double t;
    double mana;
    double mana_percent;
    int dmg;
};

struct SimulationResult
{
    int dmg;
    double t;
    double dps;
    std::string log;
};

struct SimulationsResult
{
    double min_dps, avg_dps, max_dps;
    int iterations;
};

double critRatingToChance(double rating)
{
    return rating / 22.08;
}

double hitRatingToChance(double rating)
{
    return rating / 12.62;
}

double hasteRatingToHaste(double rating)
{
    return rating / 15.75;
}

template<typename Numeric, typename Generator = std::mt19937>
Numeric random(Numeric from, Numeric to)
{
    thread_local static Generator gen(std::random_device{}());

    using dist_type = typename std::conditional
    <
        std::is_integral<Numeric>::value
        , std::uniform_int_distribution<Numeric>
        , std::uniform_real_distribution<Numeric>
    >::type;

    thread_local static dist_type dist;

    return dist(gen, typename dist_type::param_type{from, to});
}