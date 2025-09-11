import React, {useEffect, useState} from "react";
import { Trash} from "lucide-react";
// Pokedex Web App (single-file React component)
// Parser aggiornato per file stile gen_X_families.h
// - Nome Pokémon: [SPECIES_NAME] =
// - Statistiche: .baseHP, .baseAttack, .baseDefense, .baseSpeed, .baseSpAttack, .baseSpDefense
// - Tipi: .types = MON_TYPES(TYPE_X, TYPE_Y)
// - Evoluzioni: .evolutions = EVOLUTION({EVO_TYPE, VALUE, SPECIES_EVOLVED}), ...
// Quando aggiungi un Pokémon al Pokédex, vengono aggiunte automaticamente anche le sue evoluzioni.
// Le immagini vengono caricate da path: pokemon/nome_in_lowercase/front.png

export default function PokedexApp() {
    const [parsed, setParsed] = useState({});
    const [allFormsList, setAllFormsList] = useState([]);
    const [dexEntries, setDexEntries] = useState([]);
    const [query, setQuery] = useState("");
    const [lastParseLog, setLastParseLog] = useState("");

    useEffect(() => {
        const forms = [];
        Object.values(parsed).forEach((s) => {
            s.forms.forEach((f) => {
                forms.push({ speciesKey: s.speciesKey, speciesName: s.speciesName, formName: f.formName, types: f.types, baseStats: f.baseStats, evolutions: f.evolutions, imagePathGuess: f.imagePathGuess });
            });
        });
        setAllFormsList(forms);
    }, [parsed]);

    // --- funzione per esportare il Pokédex in JSON ---
    function exportDex() {
        const dataStr = JSON.stringify(dexEntries, null, 2); // formattato
        const blob = new Blob([dataStr], { type: "application/json" });
        const url = URL.createObjectURL(blob);
        const link = document.createElement("a");
        link.href = url;
        link.download = "pokedex.json";
        link.click();
        URL.revokeObjectURL(url);
    }

    // --- funzione per importare un file JSON ---
    function importDex(e) {
        const file = e.target.files[0];
        if (!file) return;

        const reader = new FileReader();
        reader.onload = (event) => {
            try {
                const imported = JSON.parse(event.target.result);
                if (Array.isArray(imported)) {
                    setDexEntries(imported);
                } else {
                    alert("File JSON non valido: deve contenere un array di Pokémon.");
                }
                // eslint-disable-next-line no-unused-vars
            } catch (err) {
                alert("Errore durante il parsing del JSON.");
            }
        };
        reader.readAsText(file);
    }


    function speciesKeyFromName(name) {
        return name.toLowerCase();
    }

    function handleFilesChange(e) {
        const f = Array.from(e.target.files || []);
        parseFiles(f).then(() => {console.log("Parsed all files")});
    }

    function getImagePath(f) {
        let subdir;
        f.formName = f.formName.replace("_totem", "");
        f.formName = f.formName.replace(/_meteor.*/, "_meteor");
        f.formName = f.formName.replace(/toxtricity_.*_gmax/, "toxtricity_gmax");
        if (f.formName.includes("minior_core")) {
            return "pokemon/minior/core/front.png";
        }
        const specialPkmn = ["burmy", "pikachu", "wormadam", "cherrim", "shellos", "gastrodon", "rotom", "dialga", "palkia", "giratina", "shaymin", "unown", "darmanitan", "basculin", "basculegion", "sawsbuck", "meloetta", "kyurem", "tornadus", "thundurus", "landorus", "keldeo", "meowstic", "aegislash", "pumpkaboo", "gourgeist", "zygarde", "xerneas", "hoopa", "furfrou", "vivillon", "greninja", "oricorio", "lycanroc", "wishiwashi", "minior", "mimikyu", "necrozma", "magearna", "cramorant", "toxtricity", "alcremie", "eiscue", "morpeko", "zacian", "zamazenta", "zarude", "urshifu", "calyrex", "enamorus", "indeedee", "oinkologne", "maushold", "palafin", "tatsugiri", "gimmighoul", "ogerpon", "terapagos", "pichu", "dudunsparce", "ursaluna", "castform", "kyogre", "groudon", "deoxys"]
        if (specialPkmn.some((e) => f.formName.toLowerCase().includes(e))) {
            f.formName = f.formName.replace(/alcremie_(.*?)_.*/, "alcremie_$1");
            f.formName = f.formName.replace("_power_construct", "");
            f.formName = f.formName.replace(/10.*/, "10_percent");
            f.formName = f.formName.replace("pokeball", "poke_ball");
            f.formName = f.formName.replace("battle_bond", "ash");
            f.formName = f.formName.replace("original", "original_color");
            f.formName = f.formName.replace("n_crowned", "n_crowned_sword");
            f.formName = f.formName.replace("a_crowned", "a_crowned_shield");
            f.formName = f.formName.replace("noice", "noice_face");
            subdir = f.formName.match(/_.*/);

            const exception = ["_overcast", "_plant", "_west", "_altered", "_land", "_red_striped", "_m", "_standard", "_spring", "_aria", "_incarnate", "_ordinary", "_shield", "_average", "_50", "_neutral", "_confined", "_natural", "_icy_snow", "10_percent", "_baile", "_midday", "_solo", "_meteor", "_disguised", "_amped", "_phony", "_ice", "_full_belly", "_hero", "_single_strike", "_m", "_zero", "_curly", "_chest", "_teal", "_normal", "_three", "_original", "_starter", "_two_segment"];
            if (subdir && exception.includes(subdir[0]) && f.formName !== "palafin_hero") return `pokemon/${f.formName.replace(subdir[0], "")}/anim_front.png`;
        } else {
            subdir = f.formName.match(/_(mega|hisui|gmax|alola|galar|paldea|eternamax).*/);
        }
        const specialPath = ["silvally", "arceus", "mothim", "scatterbug", "spewpa", "deerling", "genesect", "flabebe", "florges", "floette", "rockruff", "sinistea", "polteageist", "squawkabilly", "poltchageist", "sinistcha"];
        if (specialPath.some((e) => f.formName.toLowerCase().includes(e))) {
            subdir = f.formName.match(/_.*/);
            return `pokemon/${subdir ? f.formName.replace(subdir[0], "") : f.formName}/anim_front.png`;
        }
        if (subdir) {
            return `pokemon/${f.formName.replace(subdir[0], "")}/${subdir[0].substring(1, subdir[0].length)}/anim_front.png`;
        }
        return `pokemon/${f.formName}/anim_front.png`;
    }

    async function parseFiles(fileList) {
        const speciesMap = {};
        let log = "";
        for (const file of fileList) {
            try {
                const text = await file.text();
                const lines = text.split(/\r?\n/);
                let currentSpecies = null;
                let currentData = null;

                for (let line of lines) {
                    // Nome Pokémon
                    const nameMatch = line.match(/\[SPECIES_([A-Z0-9_]+)\]/);
                    if (nameMatch) {
                        if (currentSpecies && currentData) {
                            pushParsed(speciesMap, currentSpecies, currentData);
                        }
                        currentSpecies = nameMatch[1].toLowerCase();
                        currentData = { formName: currentSpecies, types: [], baseStats: {}, evolutions: [] };
                        continue;
                    }

                    if (!currentData) continue;

                    // Statistiche
                    const statMatch = line.match(/\.base(HP|Attack|Defense|Speed|SpAttack|SpDefense)\s*=\s*(\d+)/);
                    if (statMatch) {
                        const statName = statMatch[1];
                        const value = Number(statMatch[2]);
                        const map = {
                            HP: "hp",
                            Attack: "atk",
                            Defense: "def",
                            Speed: "spe",
                            SpAttack: "spa",
                            SpDefense: "spd",
                        };
                        currentData.baseStats[map[statName]] = value;
                    }

                    // Tipi
                    const typeMatch = line.match(/\.types\s*=\s*MON_TYPES\(([^)]+)\)/);
                    if (typeMatch) {
                        currentData.types = typeMatch[1].split(",").map((t) => t.trim().replace("TYPE_", "").toLowerCase());
                    }

                    // Evoluzioni
                    const evoMatch = line.match(/EVOLUTION\(\{([^}]+)\}\)/);
                    if (evoMatch) {
                        const parts = evoMatch[1].split(",").map((p) => p.trim());
                        if (parts.length >= 3) {
                            const speciesEvo = parts[2].replace("SPECIES_", "").toLowerCase();
                            currentData.evolutions.push(speciesEvo);
                        }
                    }
                }

                if (currentSpecies && currentData) {
                    pushParsed(speciesMap, currentSpecies, currentData);
                }

                log += `Parsed ${file.name} with gen_families parser.\n`;
            } catch (err) {
                log += `Failed to read ${file.name}: ${err.message}\n`;
            }
        }

        Object.keys(speciesMap).forEach((k) => {
            const s = speciesMap[k];
            s.speciesKey = k;
            s.speciesName = s.speciesName || k;
            s.forms = s.forms.map((f) => ({
                ...f,
                imagePathGuess: getImagePath(f),
            }));
        });

        setParsed(speciesMap);
        setLastParseLog(log || "No parse log.");
    }

    function pushParsed(map, speciesName, form) {
        const speciesKey = speciesKeyFromName(speciesName);
        if (!map[speciesKey]) map[speciesKey] = { speciesKey, speciesName: speciesKey, forms: [] };
        if (!map[speciesKey].forms.some((ff) => ff.formName === form.formName)) {
            map[speciesKey].forms.push({ ...form, imagePathGuess: getImagePath(form) });
        }
    }

    function createDex() {
        setDexEntries([]);
    }

    function addToDex(speciesKey, formName) {
        const entries = [...dexEntries, { speciesKey, formName }];
        // Aggiungi evoluzioni automatiche
        const species = parsed[speciesKey];

        function recursiveEvolutions(species) {
            const form = species.forms.find((f) => f.formName === formName) || species.forms[0];
            if (form && form.evolutions) {
                form.evolutions.forEach((evo) => {
                    if (!entries.some((en) => en.speciesKey === evo)) {
                        entries.push({speciesKey: evo, formName: evo});
                        recursiveEvolutions(parsed[evo]);
                    }
                });
            }
        }

        if (species) {
            recursiveEvolutions(species);
        }
        setDexEntries(entries);
    }

    function removeFromDex(index) {
        const d = [...dexEntries]; d.splice(index, 1); setDexEntries(d);
    }

    function computeTypeDistribution() {
        const typeCounts = {};
        const speciesAdded = new Set(dexEntries.map((e) => e.speciesKey));
        speciesAdded.forEach((sk) => {
            const s = parsed[sk];
            if (!s) return;
            const typesUnion = new Set();
            s.forms.forEach((f) => { (f.types || []).forEach((t) => typesUnion.add(t)); });
            typesUnion.forEach((t) => { if (!t) return; typeCounts[t] = (typeCounts[t] || 0) + 1; });
        });
        return typeCounts;
    }

    function computeSumBaseStats() {
        const sum = { hp:0, atk:0, def:0, spa:0, spd:0, spe:0 };
        dexEntries.forEach((e) => {
            const s = parsed[e.speciesKey];
            if (!s) return;
            const f = s.forms.find((ff) => ff.formName === e.formName) || s.forms[0];
            if (!f || !f.baseStats) return;
            ['hp','atk','def','spa','spd','spe'].forEach((k) => { sum[k] += Number(f.baseStats[k] || 0); });
        });
        return sum;
    }

    const filtered = allFormsList.filter((f) => (f.formName || f.speciesName || '').toLowerCase().includes(query.toLowerCase()));

    return (
        <div className="p-4 mx-auto w-full">
            <h1 className="text-2xl font-bold mb-4">Pokedex Builder</h1>

            <section className="mb-6">
                <label className="block font-semibold">Upload up to 9 data files</label>
                <input type="file" multiple accept="*/*" onChange={handleFilesChange} className="mt-2" />
                <pre className="bg-gray-100 p-2 mt-2 text-xs whitespace-pre-wrap max-h-48 overflow-auto text-black">{lastParseLog}</pre>
            </section>

            <section className="mb-6 flex items-center gap-4">
                <label className="font-semibold">Reset Pokédex</label>
                <button type="button" onClick={()=>createDex()} className="border p-1 w-24 flex justify-center"><Trash /></button>
            </section>

            <section className="mb-6 grid grid-cols-1 md:grid-cols-4 gap-4">
                <div className="col-span-2">
                    <input placeholder="search by name" value={query} onChange={(e) => setQuery(e.target.value)}
                           className="w-full border p-2 mb-2"/>
                    <div className="grid grid-cols-3 md:grid-cols-6 gap-3">
                        {filtered.map((f, idx) => (
                            <div key={idx} className="border rounded p-2 text-center">
                                <img src={f.imagePathGuess} alt={f.formName} className="max-h-16 mx-auto"
                                     onError={(e) => {
                                         const target = e.currentTarget;
                                         if (target.src.includes("anim_front.png")) {
                                             target.src = target.src.replace("anim_", "");
                                         } else {
                                             target.onerror = null; // ultima chance
                                             target.src = "/pokemon/question_mark.png"; // immagine di default
                                         }
                                     }}/>
                                <div className="text-xs truncate">{f.formName}</div>
                                <button className="mt-2 px-2 py-1 text-sm rounded bg-green-500 text-white"
                                        onClick={() => addToDex(f.speciesKey, f.formName)}>Add
                                </button>
                            </div>
                        ))}
                    </div>
                </div>

                <div className="col-span-1">
                    <h2 className="font-semibold">Current Pokédex ({dexEntries.length})</h2>
                    <div className="flex gap-4 mt-4">
                        <button
                            onClick={exportDex}
                            className="bg-blue-500 text-white px-4 py-2 rounded"
                        >
                            Esporta Pokédex
                        </button>

                        <label className="bg-green-500 text-white px-4 py-2 rounded cursor-pointer">
                            Importa Pokédex
                            <input
                                type="file"
                                accept="application/json"
                                className="hidden"
                                onChange={importDex}
                            />
                        </label>
                    </div>
                    <div className="mt-2 space-y-2">
                        {dexEntries.map((d, i) => {
                            const s = parsed[d.speciesKey];
                            const f = s?.forms.find(ff => ff.formName === d.formName) || s?.forms[0] || {};
                            return (
                                <div key={i} className="flex items-center gap-2 border p-2 rounded">
                                    <img src={f.imagePathGuess} alt={d.formName} className="w-12 h-12 object-contain"/>
                                    <div className="flex-1 text-sm">
                                        <div>{d.formName}</div>
                                        <div className="text-xs text-gray-600">{(f.types || []).join(', ')}</div>
                                    </div>
                                    <button onClick={() => removeFromDex(i)}
                                            className="px-2 py-1 bg-red-400 text-white rounded">X
                                    </button>
                                </div>
                            );
                        })}
                    </div>
                </div>
                <div className="col-span-1">
                    <div className="mt-4">
                        <h3 className="font-semibold">Statistics</h3>
                        <div className="mt-2">
                            {Object.entries(computeTypeDistribution()).map(([t, c]) => (
                                <div key={t} className="text-sm">{t}: {c}</div>
                            ))}
                            <div className="mt-3 text-sm">
                                {(() => {
                                    const s = computeSumBaseStats();
                                    return (
                                        <div>
                                            HP: {s.hp} · ATK: {s.atk} · DEF: {s.def} · SpA: {s.spa} · SpD: {s.spd} ·
                                            SPE: {s.spe}
                                        </div>
                                    );
                                })()}
                            </div>
                        </div>
                    </div>
                </div>
            </section>
        </div>
    );
}
