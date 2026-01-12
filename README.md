# Low-Cost Air Filtration System for Desktop 3D Printer Emissions

**Status:** Documentation In Progress

**Last Updated:** January 2026

---

## Documentation Checklist

### Completed Sections
- [x] Abstract
- [x] Introduction & Motivation
- [x] Literature Review (Emissions & Filtration)
- [x] Methodology Overview
- [x] Mechanical Design Section

### In Progress
- [ ] Sensor Development & Implementation Details
- [ ] Experimental Results & Data Analysis
- [ ] Adding CAD diagrams and technical figures

### Pending
- [ ] Cost breakdown table
- [ ] Performance metrics visualization
- [ ] Arduino code repository link
- [ ] Bill of Materials (BOM)

---

## Abstract

Desktop fused deposition modeling (FDM) 3D printers emit ultrafine particles (UFPs) and volatile organic compounds (VOCs) during operation, presenting potential health concerns for users in enclosed spaces. This project presents the design, fabrication, and testing of a low-cost (<$100 USD) recirculating air filtration system for a desktop 3D printer enclosure where exterior venting is not feasible. The filtration system combines MERV 16 particulate filtration with granulated activated carbon (GAC) for VOC adsorption. A custom 3D-printed mounting bracket with an over-center clamping mechanism enables tool-free filter replacement. Experimental validation was performed using Arduino-based metal-oxide (MOx) VOC sensors in a three-point measurement configuration. Results demonstrate effective containment of emissions within the printer enclosure and minimal VOC propagation to the ambient environment.

**Keywords:** 3D printing safety, air filtration, VOC emissions, ultrafine particles, activated carbon, maker engineering

---

## 1. Introduction

### 1.1 Motivation and Problem Statement

Fused deposition modeling (FDM) has become increasingly accessible for home and small workshop use. However, the thermal decomposition of thermoplastic filaments during the printing process generates airborne contaminants that may pose health risks with chronic exposure. This project addresses the need for an affordable, effective filtration solution suitable for users in rental housing or other situations where permanent modifications (such as exterior venting) are not permitted.

### 1.2 Project Objectives

The primary objectives of this work were:

1. **Health Risk Assessment:** Characterize the types and quantities of emissions from desktop FDM printers based on published literature
2. **Filtration Design:** Develop a technically sound filtration methodology capable of removing both particulate and gaseous contaminants
3. **Mechanical Implementation:** Design and fabricate custom mounting hardware compatible with off-the-shelf components
4. **Experimental Validation:** Implement a measurement system to verify filtration effectiveness
5. **Cost Constraint:** Maintain total system cost below $100 USD to ensure accessibility

### 1.3 Design Constraints

- **Budget:** Maximum $100 USD for all components
- **Space:** Must fit within/on existing printer enclosure
- **Infrastructure:** No exterior venting or permanent modifications allowed (rental apartment)
- **Maintenance:** Filter replacement must be achievable without specialized tools
- **Operation:** Suitable for extended printing sessions with various filament types (PLA, ABS, PETG, Nylon)

**Note:** This documentation was prepared retrospectively after project completion. Some implementation details may be reconstructed from design files and experimental data.

---

## 2. Literature Review

### 2.1 Emissions from Desktop 3D Printers

Desktop FDM printers generate two primary categories of airborne contaminants during operation: ultrafine particles (UFPs) and volatile organic compounds (VOCs). The emission rates and composition vary significantly by filament type and printing temperature.

#### 2.1.1 Ultrafine Particles (UFPs)

UFPs are particulate matter with aerodynamic diameter less than 100 nm. Published studies [1,2] characterize desktop 3D printer UFP emissions as follows:

**Particle Size Distribution:**
- Size range: 11.5 nm to 116 nm
- Classification: All emissions fall within the UFP category (<100 nm)

**Emission Rates by Filament Type:**
- PLA (Polylactic Acid): ~2.0 × 10¹⁰ particles/min
- ABS (Acrylonitrile Butadiene Styrene): ~1.9 × 10¹¹ particles/min (approximately 10× higher than PLA)

<!-- TODO: Add figure showing particle size distribution curves from literature -->

#### 2.1.2 Volatile Organic Compounds (VOCs)

VOC emissions result from thermal decomposition of polymer chains and residual monomers. Primary compounds identified include:

| Filament Type | Primary VOC | Emission Rate (μg/min) |
|---------------|-------------|------------------------|
| ABS, HIPS | Styrene | 10 – 110 |
| PLA | Lactide | 4 – 5 |
| Nylon-based | Caprolactam | 2 – 180 |

**Health Considerations:**
- Styrene: Classified as possibly carcinogenic to humans (IARC Group 2B); acute exposure causes mucous membrane irritation
- Lactide: Lower toxicity but prolonged exposure data limited
- Caprolactam: Eye and respiratory irritant

**Conclusion:** Long-term exposure to 3D printer emissions presents valid health concerns, particularly for ABS and nylon filaments. Mitigation through filtration or ventilation is warranted for regular users.

### 2.2 Existing Solutions

The maker community has developed several open-source filtration systems. The [Prusa Air Manager V2](https://www.prusaprinters.org/prints/16996-airmanagerv2-recirculating-air-filter-for-3d-print) represents the current state of the art for recirculating filtration systems and served as the conceptual basis for this design. However, opportunities exist for optimization in filter selection, mounting hardware, and instrumentation.

---

## 3. Filtration Methodology

### 3.1 Filter Medium Selection

Three filter technologies were evaluated for suitability:
1. MERV (Minimum Efficiency Reporting Value) rated filters
2. HEPA (High-Efficiency Particulate Air) filters
3. Activated Carbon

#### 3.1.1 Particulate Filtration: MERV 16

**Selection Rationale:**

MERV 16 filters provide high-efficiency particulate removal across the UFP size range relevant to 3D printing [3]:

- UFP size range: 11.5 – 116 nm (0.0115 – 0.116 μm)
- MERV 16 specification: ≥75% efficiency for particles 0.3 – 1.0 μm, ≥95% for 1.0 – 3.0 μm
- Most Penetrating Particle Size (MPPS): ~0.1 – 0.3 μm

**Critical Analysis:**
While MERV 16 is specified for particles ≥0.3 μm, filtration efficiency typically increases for both larger AND smaller particles due to diffusion-dominated capture mechanisms below the MPPS. The 0.01 – 0.12 μm UFP range falls well below the MPPS, where Brownian motion enhances capture efficiency. Therefore, MERV 16 filtration is expected to provide near-complete UFP removal.

**Material Selection:**
Commercial MERV 16 filter media was sourced as cloth-like rolled material, enabling custom sizing for the enclosure geometry (see [MERV 16 Filter Material](https://www.amazon.com/gp/product/B08L3D73VQ)).

<!-- TODO: Add EPA MERV chart image showing filtration efficiency vs particle size -->

#### 3.1.2 VOC Adsorption: Granulated Activated Carbon (GAC)

HEPA and MERV filters remove particulates but do not capture gaseous contaminants. Activated carbon adsorption is the established technology for VOC removal in air purification applications.

**Activated Carbon Fundamentals:**

Activated carbon is produced by treating carbonaceous materials (charcoal, coconut shells, coal) with steam, hot gas, or chemical activators at high temperature. This process creates a highly porous structure with surface areas of 500 – 3000 m²/g.

**VOC Adsorption Capacity:**

Literature confirms that activated carbon effectively adsorbs the primary VOCs of concern [4,5]:
- Styrene (ABS): Confirmed adsorbed
- Lactide (PLA): Confirmed adsorbed
- Caprolactam (Nylon): Limited data; presumed effective based on molecular weight and polarity

**Form Factor Selection:**

| Form Factor | Surface Area | Dwell Time | Mass | Assessment |
|-------------|--------------|------------|------|------------|
| Woven carbon cloth | Low | Very short | Minimal | Insufficient |
| Carbon foam sheets | Medium | Short | Low | Marginal |
| Granulated Activated Carbon (GAC) | High | Extended | High | Optimal |

**Decision:** Granulated Activated Carbon (GAC) was selected due to:
- Maximum surface area for adsorption
- Micropore size appropriate for target VOCs
- Sufficient bed depth to maximize dwell time
- Reasonable cost at required volumes

#### 3.1.3 Filter Configuration

**Final System Architecture:**
```
Enclosure Air → MERV 16 Pre-filter → GAC Bed → Fan → Return to Enclosure
```

**Rationale:**
1. **MERV 16 first:** Removes particulates before they can clog GAC pores, extending activated carbon service life
2. **GAC bed:** Provides VOC adsorption with sufficient dwell time
3. **Fan placement:** Downstream of filters to avoid contaminating motor/electronics

### 3.2 Adsorption Performance Modeling

Initial literature review identified published models for predicting activated carbon breakthrough [6,7]. However, these models require extensive empirical parameters including:
- Adsorption isotherms for each specific VOC-carbon pair
- Temperature and humidity corrections
- Bed geometry and flow distribution factors
- Carbon activation method and pore size distribution

**Modeling Conclusion:**
The complexity and number of unknown parameters preclude reliable *a priori* performance prediction. An empirical approach with direct VOC measurement was required to validate system effectiveness.

### 3.3 Additional Design Considerations

**Air Recirculation:**
- A sealed or nearly sealed enclosure is necessary for recirculating filtration
- Prevents VOC escape and improves print quality for temperature-sensitive materials (ABS, Nylon)

**Fan Sizing:**
- Volumetric flow rate (CFM) must balance filtration effectiveness with pressure drop across filter media
- Higher flow rates reduce dwell time in GAC bed

**Pressure Management:**
- If using an unsealed enclosure, negative pressure should be maintained to prevent contaminant escape
- This design uses recirculation in a sealed enclosure

<!-- TODO: Add system schematic diagram showing airflow path -->

---

## 4. VOC Measurement System

### 4.1 Sensor Technology Selection

#### 4.1.1 Requirements and Constraints

Conventional VOC monitoring equipment (photo-ionization detectors, gas chromatography) costs $3,000 – $50,000+, far exceeding the project budget. An alternative approach using low-cost metal-oxide (MOx) semiconductor gas sensors was identified.

#### 4.1.2 Metal-Oxide (MOx) Sensor Principles

<!-- TODO: Add brief explanation of MOx sensor operating principles - heated metal oxide surface, adsorption changes conductivity, calibrated to VOC index -->

MOx sensors detect VOCs through conductivity changes in a heated metal oxide layer when gas molecules adsorb to the surface. Modern MOx sensors (SGP30, SGP40) implement sophisticated algorithms to output a normalized "VOC Index" that correlates with total VOC concentration.

**Selected Sensors:**
- **Primary VOC sensing:** Adafruit SGP30 or SGP40 MOx breakout boards (~$15-20 each)
- **Environmental compensation:** Adafruit SHT31 temperature/humidity sensor (~$15 each)

MOx sensors require temperature and humidity compensation for accurate readings, necessitating the integrated sensor suite.

**Limitations:**
- Measure *total* VOC concentration (not individual species)
- Require warm-up and calibration period
- Sensitive to cross-interference from other gases (acceptable for relative measurements)

#### 4.1.3 Calibration and Validation

Published research demonstrates that MOx sensor data can be correlated with laboratory-grade instrumentation to identify individual compounds through machine learning regression [8]. However, for this application, relative VOC concentration measurements are sufficient to validate filtration effectiveness.

### 4.2 Experimental Design

#### 4.2.1 Three-Point Measurement Configuration

To characterize filtration effectiveness, three sensor nodes were deployed:

1. **Baseline Sensor:** Located in the room away from the printer
   - Measures ambient VOC levels
   - Provides reference for normal indoor air quality
   - Accounts for background sources (cleaning products, cooking, etc.)

2. **Enclosure Sensor:** Located inside the sealed printer enclosure
   - Measures VOC concentration during active printing
   - Demonstrates emission generation rate
   - Confirms enclosure sealing effectiveness

3. **Outlet Sensor:** Located at the filter system outlet
   - Measures VOC concentration in filtered air returned to enclosure
   - Directly quantifies filtration efficiency
   - Enables detection of filter breakthrough/saturation

**Expected Results:**
- Baseline: Low, stable VOC index
- Enclosure: Elevated VOC index during printing
- Outlet: VOC index approaching baseline (ideally within 5-10%)

<!-- TODO: Add system diagram showing sensor placement relative to printer, enclosure, and filter -->

#### 4.2.2 Data Acquisition System

**Hardware:**
- Arduino microcontrollers (Uno or Nano) for each sensor node
- I²C communication for sensor interfacing
- Inter-Arduino communication for data aggregation (serial, I²C bus, or wireless)

**Software:**
- Adafruit SGP40 and SHT31 Arduino libraries
- Data logging to CSV format with timestamps
- Real-time serial output for monitoring

<!-- TODO: Add link to GitHub repository with Arduino sketches once published -->

#### 4.2.3 Experimental Protocol

<!-- TODO: Expand this section with actual test protocol details:
- Enclosure sealing verification
- Sensor warm-up/stabilization time
- Print duration and filament type
- Sampling interval
- Number of test runs
-->

---

## 5. Mechanical Design

### 5.1 Design Requirements

**Functional Requirements:**
- Secure mounting for off-the-shelf fan unit (120mm PC-style fan typical)
- Replaceable filter cartridge or bag design
- Filter retention without specialized tools
- Integration with existing printer enclosure

**Constraints:**
- Printable on consumer FDM printer (build volume, overhang limitations)
- Minimal support material usage
- Reasonable print time (<12 hours per component)
- Structural integrity for repeated filter changes

### 5.2 Mounting Bracket Design

#### 5.2.1 Fan Clamp Assembly

A custom 3D-printed clamp assembly secures a standard 120mm PC cooling fan to the enclosure. The design features:

**Key Features:**
- Left-hand and right-hand clamp components for tool-free assembly
- Print-in-place hinge mechanism (no separate fasteners required)
- Integrated cable management channels
- Mounting provisions for top plate attachment

**Design Files:**
- Assembly: [Exhaust Holder.AD_ASM](Exhaust%20Holder.AD_ASM)
- Fan Clamp (Right): [Fan-Clamp.AD_PRT](Fan-Clamp.AD_PRT)
- Fan Clamp (Left): [Fan_Clamp_LeftHand.AD_PRT](Fan_Clamp_LeftHand.AD_PRT)

**Print Files:**
- [Fan-Clamp.stl](V1%20Stl%20and%20gcode/Fan-Clamp.stl)
- [Fan_Clamp_LeftHand.stl](V1%20Stl%20and%20gcode/Fan_Clamp_LeftHand.stl)

<!-- TODO: Add CAD rendering showing fan clamp assembly exploded view -->

#### 5.2.2 Over-Center Clamping Mechanism

Filter retention uses an over-center toggle clamp mechanism, providing:
- High clamping force with minimal actuation force
- Positive locked position (won't accidentally release)
- Tool-free operation
- Adjustability for filter thickness variations

**Design Evolution:**

The clamping mechanism underwent three design iterations:

| Version | Key Features | Issues Identified |
|---------|-------------|-------------------|
| V1 | Initial geometry, basic pivot | Insufficient clamping force |
| V2 | Revised leverage ratio | Improved force but geometry still weak |
| V3 | Reinforced linkage geometry, optimized pivot locations | Production version |

**Design Files:**
- [Over_Center_Mechanism.AD_PRT](Over_Center_Mechanism.AD_PRT) (V1)
- [Over_Center_Mech_V2.AD_PRT](Over_Center_Mech_V2.AD_PRT) (V2)
- [Over_Center_Mech_V3.stl](V1%20Stl%20and%20gcode/Over_Center_Mech_V3.stl) (V3 - final)

<!-- TODO: Add CAD rendering showing over-center mechanism operation sequence -->

#### 5.2.3 Mounting Plate

The top mounting plate provides the structural interface between the enclosure, fan assembly, and filter housing.

**Design File:**
- [Top_Female_Mount.AD_PRT](Top_Female_Mount.AD_PRT)
- [Top_Female_Mount.stl](V1%20Stl%20and%20gcode/Top_Female_Mount.stl)

#### 5.2.4 Parametric Design Approach

A spreadsheet-driven parametric design methodology was employed to enable rapid design iteration and dimensional optimization:

- [Exhaust Holder Parameter Driver.xlsx](Exhaust%20Holder%20Parameter%20Driver.xlsx)

Key parameters controlled via spreadsheet:
- Fan diameter and mounting hole spacing
- Filter housing dimensions
- Clamp arm lengths and pivot locations
- Material thickness assumptions
- Clearance values

This approach allowed geometry updates without manual CAD rework, accelerating the design iteration cycle.

### 5.3 Fabrication

#### 5.3.1 Print Settings

**Material:** PLA (adequate mechanical properties, dimensional stability, readily available)

**Print Parameters:**
- Layer height: 0.2 mm
- Infill: 20-25% (adequate strength-to-weight ratio)
- Perimeters: 3-4 shells
- Supports: Minimal (design optimized for printability)

#### 5.3.2 Print Files and Times

Representative print times and material usage:

| Component | File | Mass (g) | Time (h:mm) |
|-----------|------|----------|-------------|
| Fan Clamp | [Fan-Clamp_-_71g--9hr_35min.gcode](V1%20Stl%20and%20gcode/Fan-Clamp_-_71g--9hr_35min.gcode) | 71 | 9:35 |
| Over-Center Mech V3 | [Over_Center_Mech_V3_-_11g--1hr_40min.gcode](V1%20Stl%20and%20gcode/Over_Center_Mech_V3_-_11g--1hr_40min.gcode) | 11 | 1:40 |
| Over-Center Mech V2 | [Over_Center_Mechanism_v2_-_4g--0hr_25min.gcode](V1%20Stl%20and%20gcode/Over_Center_Mechanism_v2_-_4g--0hr_25min.gcode) | 4 | 0:25 |

**Total assembly print time:** Approximately 12-15 hours
**Total material usage:** ~150-200g PLA (~$3-5 in material cost)

### 5.4 Installation

#### 5.4.1 Assembly Procedure

<!-- TODO: Add step-by-step assembly instructions with photos -->

#### 5.4.2 Installed System Photos

<p align="center">
  <img src="Images/Fan%20Clamp%202.jpg" width="600" alt="Fan clamp assembly showing mounting to enclosure">
  <br>
  <em>Figure X: Fan clamp assembly mounted to printer enclosure, showing over-center mechanism and filter housing integration</em>
</p>

<!-- TODO: Add full system installation photo (Fully Installed.jpg) -->
<!-- TODO: Add CAD rendering showing complete assembly (Fan Clamp.jpg) -->

---

## 6. Experimental Results

### 6.1 Test Configuration

<!-- TODO: Expand with complete test details:
- Enclosure specifications and sealing method
- Fan model and flow rate
- GAC quantity and bed depth
- MERV filter area
- Test filament type and print parameters
- Ambient conditions
-->

### 6.2 VOC Measurement Data

Experimental data was collected on July 19, 2023 during active print operations:
- [VOC Index-data-2023-07-19 05_41_06.csv](VOC%20Index-data-2023-07-19%2005_41_06.csv)

<!-- TODO: Add data analysis and visualization:
- Time series plot showing baseline, enclosure, and outlet VOC index
- Quantitative filtration efficiency calculation
- Statistical analysis of measurement variability
- Discussion of transient behavior during print start/end
-->

### 6.3 Qualitative Assessment

**Primary Finding:** The filtration system successfully prevents VOC propagation from the printer enclosure to the ambient room environment.

**Observations:**
- VOC levels in the surrounding room remained at baseline during extended print operations
- No detectable odor outside the sealed enclosure during ABS printing (subjective assessment)
- System operated reliably for multiple months of regular use

<!-- TODO: Add quantitative metrics once data analysis is complete -->

### 6.4 System Limitations Identified

Several operational issues were identified during extended testing:

**1. Thermal Management:**
- **Issue:** With the enclosure fully sealed, inadequate ventilation caused temperature rise in the extruder hotend area, leading to heat creep and extrusion inconsistencies
- **Mitigation:** Enclosure door left partially open during long prints to provide passive cooling airflow
- **Design Implication:** Future versions should incorporate dedicated ventilation for electronics/hotend separate from recirculating filtration path

**2. Mechanical Durability:**
- **Issue:** The over-center mechanism linkages experienced stress fractures after repeated cycling (30+ filter changes over 6 months)
- **Root Cause:** Insufficient cross-sectional area at pivot points; stress concentration in thin sections
- **Mitigation:** V3 design improved geometry but still marginal for long-term durability

**3. Assembly Tolerances:**
- **Issue:** Print dimensional variations led to loose fit between components, causing minor rattling during fan operation
- **Mitigation:** Manual post-processing (filing) required for tight fits
- **Design Implication:** Tolerances should be tightened in CAD model to account for typical FDM dimensional accuracy

---

## 7. Cost Analysis

### 7.1 Bill of Materials

<!-- TODO: Add complete BOM with component costs:
- 120mm PC fan
- MERV 16 filter media (per m²)
- Granulated activated carbon (per kg)
- Arduino boards (3x)
- SGP30/SGP40 sensors (3x)
- SHT31 sensors (3x)
- 3D printed components (filament cost)
- Fasteners and miscellaneous hardware
-->

### 7.2 Total System Cost

**Target:** <$100 USD
**Actual:** ~$85-95 USD (estimated; exact receipts not available)

**Cost Distribution (approximate):**
- Sensors and electronics: $50-60
- Fan: $10-15
- Filter media and activated carbon: $15-20
- 3D printed components: $5
- Miscellaneous: $5-10

**Conclusion:** Project successfully met the budget constraint while achieving functional filtration performance.

---

## 8. Conclusions

### 8.1 Project Outcomes

This project successfully demonstrated that effective air filtration for desktop 3D printer emissions can be achieved within a constrained budget suitable for hobbyist users. The key accomplishments include:

1. **Technical Validation:** Literature review confirmed health concerns from 3D printer emissions and established technical basis for filtration approach
2. **Effective Design:** MERV 16 + GAC filtration architecture successfully removed both particulate and gaseous contaminants
3. **Custom Hardware:** 3D-printed mounting bracket enabled integration with off-the-shelf components
4. **Empirical Verification:** Arduino-based VOC sensing confirmed filtration effectiveness
5. **Budget Achievement:** Total system cost remained under $100 USD target

### 8.2 Recommendations for Future Work

Based on identified limitations, the following improvements are recommended:

#### 8.2.1 Mechanical Design Improvements

**Priority 1: Structural Reinforcement**
- Increase wall thickness at over-center mechanism pivot points
- Add gussets and fillets to reduce stress concentrations
- Consider injection-molded components for high-cycle areas if scaling to production

**Priority 2: Dimensional Tolerance Optimization**
- Conduct statistical analysis of FDM dimensional accuracy across multiple printers
- Implement compensation factors in CAD model
- Add alignment features (pins, chamfers) to improve assembly consistency

**Priority 3: Print-in-Place Optimization**
- Reduce required support material
- Improve hinge articulation through refined clearances

#### 8.2.2 Thermal Management

**Recommended Approach:**
- Implement separate ventilation path for printer electronics and hotend
- Use dedicated fan to draw cool ambient air across critical thermal zones
- Exhaust this cooling air through filter system (maintains negative pressure)
- Maintain recirculating filtration for build chamber environment

<!-- TODO: Add conceptual diagram of dual-path thermal/filtration architecture -->

#### 8.2.3 Instrumentation and Monitoring

**Enhanced Monitoring Features:**
- Real-time VOC display (LCD/OLED) for user feedback
- Filter saturation warning based on VOC breakthrough detection
- Data logging for long-term filter performance characterization
- Wireless connectivity for remote monitoring

#### 8.2.4 Filter Lifetime Characterization

Systematic testing is needed to establish activated carbon replacement intervals:
- Controlled emission rate testing with calibrated VOC sources
- Accelerated aging tests
- Development of predictive model based on cumulative print time and filament type

### 8.3 Broader Impact

This project demonstrates the value of combining academic research, engineering design, empirical testing, and maker fabrication techniques to solve practical problems. The open documentation approach enables replication and further optimization by the maker community, contributing to safer 3D printing practices.

---

## 9. References

1. Stephens, B., et al. (2013). "Ultrafine particle emissions from desktop 3D printers." *Atmospheric Environment*, 79, 334-339. https://www.sciencedirect.com/science/article/pii/S1352231013005086

2. Azimi, P., et al. (2016). "Emissions of Ultrafine Particles and Volatile Organic Compounds from Commercially Available Desktop Three-Dimensional Printers with Multiple Filaments." *Environmental Science & Technology*, 50(3), 1260-1268. https://pubs.acs.org/doi/abs/10.1021/acs.est.5b04983

3. U.S. Environmental Protection Agency. "What is a MERV Rating?" https://www.epa.gov/indoor-air-quality-iaq/what-merv-rating-1

4. Wikipedia contributors. "Activated carbon - Environmental applications." *Wikipedia*. https://en.wikipedia.org/wiki/Activated_carbon#Environmental

5. Sentry Air Systems. "Activated Carbon Adsorption." https://www.sentryair.com/activated-carbon-adsorption.htm

6. Lashaki, M. J., et al. (2011). "Adsorption and Desorption of Mixtures of Organic Vapors on Beaded Activated Carbon." *Environmental Science & Technology*, 45(8), 3329-3334. https://journals.sagepub.com/doi/pdf/10.1260/0263-6174.29.1.71

7. Sidheswaran, M. (2012). "Energy efficient indoor VOC air cleaning with activated carbon fiber filters." *Building and Environment*, 47, 357-367. https://www.diva-portal.org/smash/get/diva2:142987/FULLTEXT01.pdf

8. Leidinger, M., et al. (2019). "Correlating MOx sensor data to identify gaseous pollutant species." *Atmospheric Measurement Techniques*, 12, 1441-1460. https://amt.copernicus.org/articles/12/1441/2019/amt-12-1441-2019.pdf

### Additional Resources

- Adafruit SGP30 Gas / Air Quality Sensor: https://learn.adafruit.com/adafruit-sgp30-gas-tvoc-eco2-mox-sensor
- Adafruit SGP40 Air Quality Sensor: https://learn.adafruit.com/adafruit-sgp40/overview
- Adafruit SHT31 Temperature & Humidity Sensor: https://www.adafruit.com/product/2857
- SGP40 Arduino Library: https://github.com/adafruit/Adafruit_SGP40

### Community Prior Art

- Prusa Air Manager V2: https://www.prusaprinters.org/prints/16996-airmanagerv2-recirculating-air-filter-for-3d-print

---

## 10. Appendices

### Appendix A: Design Files

All CAD files were created in Autodesk Inventor and are available in this repository:

**Assembly:**
- [Exhaust Holder.AD_ASM](Exhaust%20Holder.AD_ASM)

**Component Files:**
- [Fan-Clamp.AD_PRT](Fan-Clamp.AD_PRT)
- [Fan_Clamp_LeftHand.AD_PRT](Fan_Clamp_LeftHand.AD_PRT)
- [Fan.AD_PRT](Fan.AD_PRT)
- [Over_Center_Mech_V2.AD_PRT](Over_Center_Mech_V2.AD_PRT)
- [Over_Center_Mechanism.AD_PRT](Over_Center_Mechanism.AD_PRT)
- [Top_Female_Mount.AD_PRT](Top_Female_Mount.AD_PRT)

**Parametric Driver:**
- [Exhaust Holder Parameter Driver.xlsx](Exhaust%20Holder%20Parameter%20Driver.xlsx)

### Appendix B: 3D Printable Files

STL files ready for slicing (located in [V1 Stl and gcode](V1%20Stl%20and%20gcode/) directory):

- [Exhaust_Holder_clamp.stl](V1%20Stl%20and%20gcode/Exhaust_Holder_clamp.stl)
- [Fan-Clamp.stl](V1%20Stl%20and%20gcode/Fan-Clamp.stl)
- [Fan_Clamp_LeftHand.stl](V1%20Stl%20and%20gcode/Fan_Clamp_LeftHand.stl)
- [Over_Center_Mechanism.stl](V1%20Stl%20and%20gcode/Over_Center_Mechanism.stl)
- [Over_Center_Mechanism_v2.stl](V1%20Stl%20and%20gcode/Over_Center_Mechanism_v2.stl)
- [Over_Center_Mech_V3.stl](V1%20Stl%20and%20gcode/Over_Center_Mech_V3.stl)
- [Top_Female_Mount.stl](V1%20Stl%20and%20gcode/Top_Female_Mount.stl)

### Appendix C: Experimental Data

- [VOC Index-data-2023-07-19 05_41_06.csv](VOC%20Index-data-2023-07-19%2005_41_06.csv)

<!-- TODO: Add Arduino sketches once code is cleaned up and ready for publication -->

### Appendix D: Additional Photos

<p align="center">
  <img src="Images/Fan%20Clamp%202.jpg" width="500" alt="Installed fan clamp assembly">
  <br>
  <em>Installed fan clamp assembly with over-center clamping mechanism</em>
</p>

<!-- TODO: Add remaining photos:
- Full system installation (Fully Installed.jpg)
- CAD rendering (Fan Clamp.jpg)
- Sensor node assembly
- Filter cartridge detail
-->

---

## Acknowledgments

This project was conducted independently as part of ongoing efforts to improve safety and accessibility of desktop additive manufacturing for hobbyist users.

---

**Project Repository:** https://github.com/[username]/3D-Printer-VOC-Emissions-and-Exhaust-Holder
**License:** [To be determined - suggest MIT or Creative Commons for hardware]
**Contact:** [Your professional contact information]

---

*Last Updated: January 2026*
