#pragma once

#include "hittable.h"

#include <vector>

class hittable_list : public hittable
{
public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> obj) { objects.emplace_back(obj); }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        hit_record tmp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto &obj : objects)
        {
            if (obj->hit(r, interval(ray_t.min, closest_so_far), tmp_rec))
            {
                hit_anything = true;
                closest_so_far = tmp_rec.t;
                rec = tmp_rec;
            }
        }
        return hit_anything;
    }
};