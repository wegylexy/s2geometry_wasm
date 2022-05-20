#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <limits>
#include <s2/s2cell_id.h>
#include <s2/s2latlng.h>

emscripten::val IdToLatLng(const uint64_t id)
{
    S2CellId c{id};
    if (c.is_valid())
    {
        const auto ll = c.ToLatLng();
        return emscripten::val::array(std::vector<double>{ll.lat().degrees(), ll.lng().degrees()});
    }
    else
    {
        return emscripten::val::undefined();
    }
}

uint64_t LatLngToId(const double latitude, const double longitude)
{
    const auto ll = S2LatLng::FromDegrees(latitude, longitude);
    return (ll.is_valid() ? S2CellId{ll} : S2CellId::None()).id();
}

std::string IdToToken(const uint64_t id)
{
    return S2CellId{id}.ToToken();
}

uint64_t TokenToId(const std::string &token)
{
    return S2CellId::FromToken(token).id();
}

using namespace emscripten;

EMSCRIPTEN_BINDINGS(s2)
{
    function("IdToLatLng", &IdToLatLng);

    function("LatLngToId", &LatLngToId);

    function("IdToToken", &IdToToken);

    function("TokenToId", &TokenToId);
}